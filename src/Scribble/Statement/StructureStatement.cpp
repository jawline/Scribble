/*
 * StructureStatement.cpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#include "StructureStatement.hpp"
#include <Scribble/Value/StructureInfo.hpp>
#include <VM/Constants.hpp>

namespace ScribbleCore {

StructureStatement::StructureStatement(int lineno, std::string token,
                                       TypeReference type, std::vector<SafeStatement> statements) :
    Statement(lineno, token), type_(type), statements_(statements) {

}

StructureStatement::~StructureStatement() {
}

void StructureStatement::checkTree(Type* functionType) {

    for (unsigned int i = 0; i < statements_.size(); ++i) {
        statements_[i]->checkTree(functionType);
    }

    StatementAssert(this, type()->type()->getType() == StructureType,
                    std::string() + "the type " + type()->type()->getTypeName()
                    + " does not need a structure constructor");

    StructureInfo* info = (StructureInfo*) type()->type();

    if (info->getNumFields() != statements_.size()) {
        std::stringstream errormsg;
        errormsg
                << "invalid number of arguments supplied to constructor. The structure "
                << info->getName() << " requires " << info->getNumFields()
                << " arguments but only " << statements_.size()
                << " argument was supplied";
        throw StatementException(this, errormsg.str());
    }

    for (unsigned int i = 0; i < statements_.size(); ++i) {

        if (!(statements_[i]->type()->type()->Equals(
                    info->getField(i).second->type())
                || statements_[i]->type()->type()->getType() == NilType)) {

            std::stringstream errorMsg;
            errorMsg << "the constructor argument " << i << " is a "
                     << statements_[i]->type()->type()->getTypeName()
                     << " however a "
                     << info->getField(i).second->type()->getTypeName()
                     << " was expected";
            throw StatementException(this, errorMsg.str());
        }

    }

}

TypeReference StructureStatement::type() {
    return type_;
}

int StructureStatement::generateCode(int result, std::stringstream& code) {

    int instrs = 0;

    //Create the structure reference
    code << "newstruct \"" << type()->type()->getTypeName() << "\" $"
         << VM::vmTempRegisterOne << "\n";
    instrs += 1;

    //For each argument in the constructor
    for (unsigned int i = 0; i < statements_.size(); i++) {

        //Push the array register
        code << "pushr $" << VM::vmTempRegisterOne << " 1\n";
        instrs++;

        // Put the arguments value in temp register 2
        instrs += statements_[i]->generateCode(VM::vmTempRegisterTwo, code);

        //Load the field index into a register
        code << "load " << i << " $" << VM::vmTempRegisterThree << "\n";
        instrs++;

        //Pop the array register
        code << "popr $" << VM::vmTempRegisterOne << " 1\n";
        instrs++;

        //Place the value into the structure field.
        code << "sset $" << VM::vmTempRegisterOne << " $"
             << VM::vmTempRegisterThree << " $" << VM::vmTempRegisterTwo
             << "\n";

        instrs++;
    }

    if (result != VM::vmTempRegisterOne) {

        //Move the array reference into the result register.
        code << "move $" << VM::vmTempRegisterOne << " $" << result << "\n";
        instrs++;

    }

    return instrs;
}

}
