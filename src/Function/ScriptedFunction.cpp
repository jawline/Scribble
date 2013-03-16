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
		std::vector<SmartPointer<Variable>> variables) {
	statements_ = statements;
	variables_ = variables;
	fType_ = fType;
}

ScriptedFunction::~ScriptedFunction() {
}

Value* ScriptedFunction::execute(std::vector<Value*> arguments) {

	for (unsigned int i = 0; i < variables_.size(); ++i) {
		variables_[i]->getValue()->applyOperator(Assign, arguments[i]);
	}

	//Execute the statements in the function
	for (unsigned int i = 0; i < statements_.size(); ++i) {

		try {
			Value* r = statements_[i]->execute();
			delete r;
		} catch (Return r) {
			return r.val_;
		}
	}

}

ValueType ScriptedFunction::getType() {
	return fType_;
}
