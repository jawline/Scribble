/*
 * ScriptedFunction.cpp
 *
 *  Created on: 9 Mar 2013
 *      Author: blake
 */

#include "ScriptedFunction.hpp"
#include <Scribble/Statement/ReturnStatement.hpp>
#include <sstream>

std::string makeName(std::string name, int version) {

	std::stringstream funcName;
	funcName << name << "#" << version;
	return funcName.str();
}

ScriptedFunction::ScriptedFunction(std::string name, int version,
		std::string names, TypeReference fType, SmartPointer<Variable> templateReturn,
		std::vector<SmartPointer<Statement>> statements,
		std::vector<SmartPointer<Variable>> templates,
		std::vector<SmartPointer<Variable>> arguments) :
		Function(makeName(name, version), names), fType_(fType), templateReturn_(
				templateReturn), statements_(statements), variableTemplates_(
				templates), arguments_(arguments) {

}

ScriptedFunction::~ScriptedFunction() {
}

Type* ScriptedFunction::getType() {
	return fType_->type;
}

void ScriptedFunction::check() {

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->checkTree(getType());
	}

}

Type* ScriptedFunction::argType(unsigned int arg) {

	if (numArgs() <= arg) {
		return getTypeManager().getType(TypeUnresolved);
	}

	return arguments_[arg]->getType();
}

const unsigned int ScriptedFunction::numArgs() {
	return arguments_.size();
}

int ScriptedFunction::debugCode(std::stringstream& gen) {
	int script = 0;

	for (int i = arguments_.size() - 1; i >= 0; i--) {
		gen << "popr $"
				<< VM::vmNumReservedRegisters + arguments_[i]->getPosition()
				<< " 1\n";
		script += 1;
	}

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		script += statements_[i]->generateCode(5, gen);
	}

	return script;
}
