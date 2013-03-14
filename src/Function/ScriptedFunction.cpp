/*
 * ScriptedFunction.cpp
 *
 *  Created on: 9 Mar 2013
 *      Author: blake
 */

#include "ScriptedFunction.hpp"

ScriptedFunction::ScriptedFunction(
		std::vector<SmartPointer<Statement>> statements,
		std::vector<SmartPointer<Variable>> variables) {
	statements_ = statements;
	variables_ = variables;
}

ScriptedFunction::~ScriptedFunction() {
}

Value* ScriptedFunction::execute(std::vector<Value*> arguments) {

	for (unsigned int i = 0; i < variables_.size(); ++i) {
		variables_[i]->getValue()->applyOperator(Assign, arguments[i]);
	}

	//Execute the statements in the function
	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->execute();
	}

}
