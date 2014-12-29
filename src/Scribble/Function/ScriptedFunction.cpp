/*
 * ScriptedFunction.cpp
 *
 *  Created on: 9 Mar 2013
 *      Author: blake
 */

#include "ScriptedFunction.hpp"
#include <Scribble/Statement/ReturnStatement.hpp>
#include <sstream>

namespace ScribbleCore {

std::string makeName(std::string name, int version) {

    std::stringstream funcName;
    funcName << name << "#" << version;
    return funcName.str();
}

ScriptedFunction::ScriptedFunction(std::string name, int version,
                                   std::string names, std::vector<SmartPointer<Statement>> statements,
                                   std::vector<SmartPointer<Variable>> templates, FunctionSignature signature) : Function(makeName(name, version), names), statements_(statements), variableTemplates_(
                                           templates) {
    setSignature(signature);
}

ScriptedFunction::~ScriptedFunction() {
}

void ScriptedFunction::check() const {

    for (unsigned int i = 0; i < statements_.size(); ++i) {
        statements_[i]->checkTree(getSignature().getReturnType()->type());
    }

}

int ScriptedFunction::debugCode(std::stringstream& gen) {

    int script = 0;

    for (unsigned int i = 0; i < variableTemplates_.size(); i++) {
        gen << "--variable " << variableTemplates_[i]->getName() << " is at "
            << VM::vmNumReservedRegisters + i << "\n";
    }

    //The argument registers for a function are always the position of the first n variables after the reserved registers
    for (int i = signature_.getArguments().size() - 1; i >= 0; i--) {

        gen << "popr $"
            << VM::vmNumReservedRegisters
            + variableTemplates_[i]->getPosition() << " 1\n";

        script += 1;
    }

    for (unsigned int i = 0; i < statements_.size(); ++i) {
        script += statements_[i]->generateCode(-1, gen);
    }

    gen << "load 0 $" << VM::vmReturnResultRegister << "\n";
    gen << "ret\n";

    return script;
}

APIValue ScriptedFunction::execute(API::APIValue* values,
                                   VM::VirtualMachine* virt) {

    printf("ERR should not get here\nScriptedFunction\n");
    exit(1);
}

bool ScriptedFunction::isNativeFunction() const {

    return false;
}

}
