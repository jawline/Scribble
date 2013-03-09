/*
 * ScriptedFunction.cpp
 *
 *  Created on: 9 Mar 2013
 *      Author: blake
 */

#include "ScriptedFunction.hpp"

ScriptedFunction::ScriptedFunction(
		std::vector<SmartPointer<Statement>> statements) {
	statements_ = statements;
}

ScriptedFunction::~ScriptedFunction() {
}

Value* ScriptedFunction::execute(std::vector<Value*> arguments) {

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->execute();
	}

}
