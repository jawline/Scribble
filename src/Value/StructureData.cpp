/*
 * StructureData.cpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#include "StructureData.hpp"

StructureData::StructureData(unsigned int numElements, Value** initial) {
	numElements_ = numElements;
	values_ = initial;
}

StructureData::~StructureData() {

	for (unsigned int i = 0; i < numElements_; i++) {

		if (values_[i] != nullptr) {
			delete values_[i];
		}

	}

	delete[] values_;

}

