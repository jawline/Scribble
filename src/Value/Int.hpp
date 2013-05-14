/*
 * String.hpp
 *
 *  Created on: 8 Mar 2013
 *      Author: Blake Loring
 */

#ifndef _INT_H_
#define _INT_H_
#include "Value.hpp"
#include <Statement/Heap.hpp>

/**
 * Internal representation of an integer within the system.
 */

class IntValue: public Value {
private:

	/**
	 * The raw value.
	 */

	int value_;

public:

	/**
	 * Construct it with an initial value.
	 */

	IntValue(int value) {
		value_ = value;
	}

	/**
	 * Get the value type ( getIntType() )
	 */

	Type* type();

	/**
	 * Get the value of the IntValue as an int.
	 */

	int value();

	/**
	 * Set the integer value.
	 */

	void setValue(int v);

	/**
	 * Return an identical copy of the int.
	 */

	Value* clone();

	/**
	 * Apply the given operator to the value.
	 */

	void applyOperator(ValueOperator v, Value* r);
};

#endif //_INT_H_
