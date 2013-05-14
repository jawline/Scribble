/*
 * ArrayData.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef ARRAYDATA_HPP_
#define ARRAYDATA_HPP_
#include "Value.hpp"

/**
 * Array data is a structure which contains the actual array data which array values store references too.
 * Exposes length and data and frees data upon destruction ( Which should happen when no more arrays have a reference to the array data )
 */
class ArrayData {
private:

	/**
	 * Store to the length of array data.
	 */

	unsigned int length_;

	/**
	 * Pointer to a list of value pointers, Should only be nullptr if the data has been destructed.
	 */

	Value** data_;

public:

	/**
	 * Initialise the array data with a length and set of initial values. (Note: It uses the initial pointer directly so do not destruct it)
	 */

	ArrayData(unsigned int length, Value** initial);
	virtual ~ArrayData();

	/**
	 * Get the total number of indexs in the array data
	 * ( Note, As arrays can be slices of a ArrayData this may be different from a pointing arrays length )
	 */

	unsigned int dataLength() {
		return length_;
	}

	/**
	 * Return a pointer to the value of an array at a given index.
	 */

	Value* index(unsigned int i) {
		return data_[i];
	}

};

#endif /* ARRAYDATA_HPP_ */
