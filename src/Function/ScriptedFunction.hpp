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
	std::vector<SmartPointer<Variable>> variables_;
	int numArguments_;

public:
	ScriptedFunction(std::vector<SmartPointer<Statement>> statements,
			std::vector<SmartPointer<Variable>> variables);
	virtual ~ScriptedFunction();

	Value* execute(std::vector<Value*> arguments);

	ValueType type() {
		return Void;
	}

	unsigned int numArgs() {
		return variables_.size();
	}

	ValueType argType(int arg) {
		return variables_[arg]->getType();
	}
};

#endif /* SCRIPTEDFUNCTION_HPP_ */
