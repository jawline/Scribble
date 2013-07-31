/*
 * StructureData.hpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#ifndef STRUCTUREDATA_HPP_
#define STRUCTUREDATA_HPP_
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Value/Value.hpp>

class StructureData {
private:
	unsigned int numElements_;
	Value** values_;

public:
	StructureData(unsigned int size, Value** data);
	virtual ~StructureData();

	Value* get(unsigned int index) {
		return values_[index];
	}
};

typedef SmartPointer<StructureData> SafeStructureData;

#endif /* STRUCTUREDATA_HPP_ */
