/*
 * StringFunction.hpp
 *
 *  Created on: 10 Mar 2013
 *      Author: blake
 */

#ifndef STRINGFUNCTION_HPP_
#define STRINGFUNCTION_HPP_
#include "Function.hpp"
#include <Value/TypeManager.hpp>

class IntToStringFunction: public Function {
public:
	IntToStringFunction();
	virtual ~IntToStringFunction();

	Value* execute(std::vector<Value*> arguments);

	Type* getType();
	const unsigned int numArgs();
	Type* argType(unsigned int arg);

	virtual void check() {
	}
};

class BoolToStringFunction: public Function {
public:
	BoolToStringFunction();
	virtual ~BoolToStringFunction();

	Value* execute(std::vector<Value*> arguments);

	 Type* getType();
	const unsigned int numArgs();
	Type* argType(unsigned int arg);

	virtual void check() {
	}
};

#endif /* STRINGFUNCTION_HPP_ */
