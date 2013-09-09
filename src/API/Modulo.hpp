/*
 * Modulo.hpp
 *
 *  Created on: May 18, 2013
 *      Author: blake
 */

#ifndef MODULO_HPP_
#define MODULO_HPP_
#include "Function.hpp"

/**
 * Built in function which provides modulo functionality (The remainder of division) so Mod(5,3) = 2
 */

class Modulo: public Function {
private:
	std::string namespace_;

public:
	Modulo(std::string namesp);
	virtual ~Modulo();

	/**
	 * Execute the function and return the result value.
	 */

	virtual Value* execute(std::vector<Value*> arguments);

	/**
	 * Get the return type of the function.
	 */

	virtual Type* getType();

	/**
	 * Get the number of arguments (2)
	 */

	virtual const unsigned int numArgs();

	/**
	 * Get the arg type for a given argument ( Both Integer)
	 */

	virtual Type* argType(unsigned int arg);



	virtual VM::VMFunc generateVMFunction() {
		return VM::VMFunc(getName(), VM::InstructionSet());
	}
};

#endif /* MODULO_HPP_ */
