/*
 * ArrayData.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef ARRAYDATA_HPP_
#define ARRAYDATA_HPP_
#include "Value.hpp"

class ArrayData {
private:
	unsigned int length_;
	Value** data_;

public:
	ArrayData(unsigned int length, Value** initial);
	virtual ~ArrayData();

	unsigned int dataLength() {
		return length_;
	}

	Value* index(unsigned int i) {
		return data_[i];
	}
};

#endif /* ARRAYDATA_HPP_ */
