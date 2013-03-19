/*
 * ScriptedFunction.hpp
 *
 *  Created on: 9 Mar 2013
 *      Author: blake
 */

#ifndef SCRIPTEDFUNCTION_HPP_
#define SCRIPTEDFUNCTION_HPP_
#include "Function.hpp"
#include <Statement/Statement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Value/Variable.hpp>

class ScriptedFunction: public Function {
private:
	std::vector<SmartPointer<Statement>> statements_;
	std::vector<SmartPointer<Variable>> arguments_;
	int numArguments_;
	ValueType fType_;

public:
	ScriptedFunction(ValueType functionType,
			std::vector<SmartPointer<Statement>> statements,
			std::vector<SmartPointer<Variable>> variables);

	virtual ~ScriptedFunction();

	Value* execute(std::vector<Value*> arguments);

	ValueType getType();

	unsigned int numArgs() {
		return arguments_.size();
	}

	ValueType argType(int arg) {
		return arguments_[arg]->getType();
	}

	void check() {

		for (unsigned int i = 0; i < statements_.size(); ++i) {
			statements_[i]->checkTree(getType());
		}

	}
};

#endif /* SCRIPTEDFUNCTION_HPP_ */
