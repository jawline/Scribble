/*
 * Void.hpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#ifndef VOID_HPP_
#define VOID_HPP_
#include "Value.hpp"

/**
 * Representation of a void value within the system.
 */

class VoidValue: public Value {
public:
	VoidValue();
	virtual ~VoidValue();

	/**
	 * Other than assign there are no valid operators for voids.
	 */

	virtual void applyOperator(ValueOperator, Value* other);

	/**
	 * Return the void type. getVoidType()
	 */

	virtual Type* type();

	/**
	 * Clones the void. Just returns a standard void.
	 */

	virtual Value* clone();
};

#endif /* VOID_HPP_ */
