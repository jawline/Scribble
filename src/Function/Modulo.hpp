/*
 * Modulo.hpp
 *
 *  Created on: May 18, 2013
 *      Author: blake
 */

#ifndef MODULO_HPP_
#define MODULO_HPP_
#include "Function.hpp"

class Modulo: public Function {
public:
	Modulo();
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

	virtual Type* argType(unsigned int arg) ;

	/**
	 * Check (Do nothing)
	 */

	virtual void check();
};

#endif /* MODULO_HPP_ */