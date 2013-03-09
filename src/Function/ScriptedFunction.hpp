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

class ScriptedFunction: public Function {
private:
	std::vector<SmartPointer<Statement>> statements_;

public:
	ScriptedFunction(std::vector<SmartPointer<Statement>> statements);
	virtual ~ScriptedFunction();

	Value* execute(std::vector<Value*> arguments);
};

#endif /* SCRIPTEDFUNCTION_HPP_ */
