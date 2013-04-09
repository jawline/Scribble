/*
 * StringFunction.hpp
 *
 *  Created on: 10 Mar 2013
 *      Author: blake
 */

#ifndef STRINGFUNCTION_HPP_
#define STRINGFUNCTION_HPP_
#include "Function.hpp"

class IntToStringFunction: public Function {
public:
	IntToStringFunction();
	virtual ~IntToStringFunction();

	Value* execute(std::vector<Value*> arguments);

	ValueType const getType();
	const unsigned int numArgs();
	const ValueType argType(int arg);

	virtual void check() {
	}
};


class BoolToStringFunction: public Function {
public:
	BoolToStringFunction();
	virtual ~BoolToStringFunction();

	Value* execute(std::vector<Value*> arguments);

	ValueType const getType();
	const unsigned int numArgs();
	const ValueType argType(int arg);

	virtual void check() {
	}
};


#endif /* STRINGFUNCTION_HPP_ */
