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
private:
public:
	RandomInt(std::string ns);
	virtual ~RandomInt();

	Value* execute(std::vector<Value*> arguments);
	Type* getType();
	const unsigned int numArgs();
	Type* argType(unsigned int arg);

	virtual VM::VMFunc generateVMFunction() {
		return VM::VMFunc(getName(), this);
	}

};

#endif /* RANDOMINT_HPP_ */
