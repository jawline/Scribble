/*
 * Array.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef ARRAY_SYS_HPP_
#define ARRAY_SYS_HPP_
#include "Value.hpp"
#include "ArrayData.hpp"
#include <stdio.h>

class ArrayValue: public Value {
private:

	/**
	 * The start index of the array in the array data
	 */
	int start_;

	/**
	 * The length of the array
	 */
	int length_;

	/**
	 * The type of this array ( Array(Type) ).
	 */

	Type* type_;

	/**
	 * A reference to the (Potentially shared) array data that this array value is built from.
	 */
	SmartPointer<ArrayData> data_;

public:

	ArrayValue(Type* type);
	virtual ~ArrayValue();

	/**
	 * Return the type of this value.
	 */

	Type* type();

	/**
	 * Return an identical array value.
	 */

	Value* clone();

	/**
	 * Apply an operator to the array (Note: Only assign is supported).
	 */

	void applyOperator(ValueOperator v, Value* r);

	/**
	 * Get a reference to the array data.
	 */
	SP<ArrayData> getArrayData() {
		return data_;
	}

	/**
	 * Get the start index of the array in the array data
	 */

	int getStart();

	/**
	 * Get the array length
	 */

	int getLength();

	/**
	 * Set the array data, start index and length vertex.
	 */
	void setArrayData(SP<ArrayData> d, int start, int l);
};

#endif /* ARRAY_SYS_HPP_ */
