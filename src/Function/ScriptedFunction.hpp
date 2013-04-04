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

	ValueType fType_;
	SP<Value> templateReturn_;
	std::vector<SmartPointer<Statement>> statements_;
	std::vector<SmartPointer<Variable>> variableTemplates_;
	std::vector<SmartPointer<Variable>> arguments_;

public:

	ScriptedFunction(ValueType functionType,
			SP<Value> templateReturn,
			std::vector<SmartPointer<Statement>> statements,
			std::vector<SmartPointer<Variable>> variableTemplates,
			std::vector<SmartPointer<Variable>> variables);

	virtual ~ScriptedFunction();

	Value* execute(std::vector<Value*> arguments);

	const ValueType getType();

	const unsigned int numArgs() {
		return arguments_.size();
	}

	const ValueType argType(int arg) {
		return arguments_[arg]->getType();
	}

	void check() {

		for (unsigned int i = 0; i < statements_.size(); ++i) {
			statements_[i]->checkTree(getType());
		}

	}
};

#endif /* SCRIPTEDFUNCTION_HPP_ */
