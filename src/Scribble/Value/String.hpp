/*
 * String.hpp
 *
 *  Created on: 8 Mar 2013
 *      Author: Blake Loring
 */

#ifndef _STRING_H_
#define _STRING_H_
#include "Value.hpp"
#include <string>
#include <Scribble/Statement/Heap.hpp>

/**
 * Internal representation of a string within Scribble.
 */

class StringValue: public Value {
private:
	std::string value_;

public:

	StringValue(std::string const value);
	Type* type();
	Value* clone();

	/**
	 * Apply a given operator to the string.
	 * Note that only = and + are implemented.
	 */

	void applyOperator(ValueOperator v, Value* r);

	/**
	 * Get the value of the string element.
	 */

	std::string getValue();

	/**
	 * Set the value of the string to a new value.
	 */

	void setValue(std::string const& ref);
};

#endif //_STRING_H_
