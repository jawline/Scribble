/*
 * ScriptedFunction.hpp
 *
 *  Created on: 9 Mar 2013
 *      Author: blake
 */

#ifndef SCRIPTEDFUNCTION_HPP_
#define SCRIPTEDFUNCTION_HPP_
#include "Function.hpp"
#include <Scribble/Statement/Statement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Value/Variable.hpp>
#include <Scribble/Parser/TypeReference.hpp>

class ScriptedFunction: public Function {
private:

	TypeReference fType_;SP<Variable> templateReturn_;
	std::vector<SmartPointer<Statement>> statements_;
	std::vector<SmartPointer<Variable>> variableTemplates_;
	std::vector<SmartPointer<Variable>> arguments_;

public:

	ScriptedFunction(TypeReference functionType, SP<Variable> templateReturn,
			std::vector<SmartPointer<Statement>> statements,
			std::vector<SmartPointer<Variable>> variableTemplates,
			std::vector<SmartPointer<Variable>> variables);

	virtual ~ScriptedFunction();

	Value* execute(std::vector<Value*> arguments);

	Type* getType();

	const unsigned int numArgs();
	Type* argType(unsigned int arg);
	void check();

	int debugCode(std::stringstream& gen);
};

#endif /* SCRIPTEDFUNCTION_HPP_ */
