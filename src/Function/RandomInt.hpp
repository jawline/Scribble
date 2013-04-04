/*
 * RandomInt.hpp
 *
 *  Created on: 18 Mar 2013
 *      Author: blake
 */

#ifndef RANDOMINT_HPP_
#define RANDOMINT_HPP_
#include "Function.hpp"

/**
 * Random integer implementation. Returns a random integer between zero and n
 */
class RandomInt: public Function {
public:
	RandomInt();
	virtual ~RandomInt();

	Value* execute(std::vector<Value*> arguments);
	const ValueType getType();
	const unsigned int numArgs();
	const ValueType argType(int arg);
	void check();
};

#endif /* RANDOMINT_HPP_ */
