/*
 * ArrayData.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#include "ArrayData.hpp"

ArrayData::ArrayData(unsigned int length, Value** initial) :
		length_(length), data_(initial) {
}

ArrayData::~ArrayData() {

	if (data_ != nullptr) {
		for (unsigned int i = 0; i < length_; i++) {
			delete data_[i];
		}

		delete[] data_;
	}

}

