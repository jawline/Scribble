/*
 * ScriptedFunction.cpp
 *
 *  Created on: 9 Mar 2013
 *      Author: blake
 */

#include "ScriptedFunction.hpp"
#include <Statement/ReturnStatement.hpp>

ScriptedFunction::ScriptedFunction(ValueType fType,
		std::vector<SmartPointer<Statement>> statements,
		std::vector<SmartPointer<Variable>> arguments) :
		fType_(fType), statements_(statements), arguments_(arguments) {
}

ScriptedFunction::~ScriptedFunction() {
}

Value* ScriptedFunction::execute(std::vector<Value*> arguments) {

	Value** storedVariables = new Value*[arguments_.size()];

	for (unsigned int i = 0; i < arguments_.size(); ++i) {
		storedVariables[i] = arguments_[i]->getValue()->clone();
		arguments_[i]->getValue()->applyOperator(Assign, arguments[i]);
	}

	Value* returnVal = 0;

	//Execute the statements in the function
	for (unsigned int i = 0; i < statements_.size(); ++i) {

		try {
			Value* r = statements_[i]->execute(std::vector<Value*>());
			delete r;
		} catch (Return r) {
			returnVal = r.val_;
			break;
		}
	}

	for (unsigned int i = 0; i < arguments_.size(); ++i) {
		arguments_[i]->getValue()->applyOperator(Assign, storedVariables[i]);
		delete storedVariables[i];
	}

	delete[] storedVariables;

	return returnVal;
}

ValueType ScriptedFunction::getType() {
	return fType_;
}
