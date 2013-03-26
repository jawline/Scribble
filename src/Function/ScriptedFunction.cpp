/*
 * ScriptedFunction.cpp
 *
 *  Created on: 9 Mar 2013
 *      Author: blake
 */

#include "ScriptedFunction.hpp"
#include <Statement/ReturnStatement.hpp>

ScriptedFunction::ScriptedFunction(ValueType fType, SP<Value> templateReturn,
		std::vector<SmartPointer<Statement>> statements,
		std::vector<SmartPointer<Variable>> templates,
		std::vector<SmartPointer<Variable>> arguments) :
		fType_(fType), templateReturn_(templateReturn), statements_(statements), variableTemplates_(
				templates), arguments_(arguments) {
}

ScriptedFunction::~ScriptedFunction() {
}

Value* ScriptedFunction::execute(std::vector<Value*> arguments) {

	//Setup some memory for this functions variables.
	std::vector<Value*> values;

	//Setup the function variables.
	for (unsigned int i = 0; i < variableTemplates_.size(); ++i) {
		values.push_back(variableTemplates_[i]->getValue()->clone());
	}

	//Copy in the arguments that have been passed.
	for (unsigned int i = 0; i < arguments_.size(); ++i) {
		values[arguments_[i]->getPosition()]->applyOperator(Assign,
				arguments[i]);
	}

	//Initialise the returnval to null
	Value* returnVal = 0;

	//Execute the statements in the function
	for (unsigned int i = 0; i < statements_.size(); ++i) {

		//Execute each statement waiting to catch the error if a return is thrown.
		try {
			Value* r = statements_[i]->execute(values);
			delete r;
		} catch (Return &r) {
			returnVal = r.val_;
			break;
		}
	}

	// Free up memory allocated to function variables
	for (unsigned int i = 0; i < values.size(); ++i) {
		delete values[i];
	}

	//If no memory has been returned fill it with the function template
	if (returnVal == 0) {
		returnVal = templateReturn_->clone();
	}

	return returnVal;
}

ValueType ScriptedFunction::getType() {
	return fType_;
}
