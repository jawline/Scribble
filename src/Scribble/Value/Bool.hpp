/*
 * Bool.hpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#ifndef BOOL_HPP_
#define BOOL_HPP_
#include "Value.hpp"
#include <Scribble/Statement/Heap.hpp>

/**
 * Internal structure representing booleans within Scribble
 */

class BoolValue: public Value {
private:
	bool value_;

public:
	BoolValue(bool value);
	virtual ~BoolValue();

	/**
	 * Get the value of the boolean.
	 */

	bool value();

	/**
	 * Set the boolean to a new value
	 */

	void setValue(bool v);

	/**
	 * Get the type of the boolean. ( Just a call to getBooleanType() )
	 */

	Type* type();

	/**
	 * Create an identical copy of the boolean value.
	 */

	Value* clone();

	/**
	 * Apply an operator to the boolean (Only assign is valid).
	 */

	void applyOperator(ValueOperator v, Value* r);
};

#endif /* BOOL_HPP_ */
