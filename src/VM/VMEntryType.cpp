/*
 * VMEntryType.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: blake
 */

#include "VMEntryType.hpp"
#include <stdio.h>

namespace VM {

VMEntryType::VMEntryType(std::string name, unsigned int size, bool reference) :
		name_(name), size_(size), reference_(reference), baseType_(VMPrimitive), structureFieldOffsets_(
				nullptr) {

}

VMEntryType::VMEntryType(std::string name, SmartPointer<VMEntryType> subtype) :
name_(name), size_(8), reference_(true), baseType_(VMArray), arraySubtype_(subtype), structureFieldOffsets_(nullptr) {
}

VMEntryType::VMEntryType(std::string name, std::vector<SmartPointer<VMStructureField>> fields) : name_(name), size_(8), reference_(true), baseType_(VMStructure) {

	//Set the structure size to 0 and the dirty flag to true to tell the structure to recompute its size when requested.
	structureSizeBytes_ = 0;
	structureSizeDirty_ = true;

	//Because the field types are resolved after the initial type is constructed instead of
	//caching now use a dirty flag to make sure its cached before use.
	structureFieldsDirty_ = true;

	//Add the structure fields to the list
	for (unsigned int i = 0; i < fields.size(); i++) {
		structureFields_.push_back(fields[i]);
	}

	//Create a cache for the field offsets
	structureFieldOffsets_ = new int[fields.size()];

}

VMEntryType::~VMEntryType() {

	if (structureFieldOffsets_ != nullptr) {
		delete[] structureFieldOffsets_;
	}

	printf("Type %s destructed\n", typeName().c_str());

}

int VMEntryType::cacheFieldOffsets() {

	int count = 0;

	for (unsigned int id = 0; id < structureFields_.size(); ++id) {

		structureFieldOffsets_[id] = count;
		count += structureFields_[id]->getType()->getElementSize();

	}

	return count;
}

std::string VMEntryType::typeName() {
	return name_;
}

unsigned int VMEntryType::getElementSize() {
	return size_;
}

int VMEntryType::getStructureFieldOffset(unsigned int id) {

	if (structureFieldsDirty_) {
		cacheFieldOffsets();
	}

	return structureFieldOffsets_[id];
}

unsigned int VMEntryType::getStructureSize() {

	//If the structure size hasn't been calculcated since the structure was changed then recalculate it.

	if (structureSizeDirty_) {

		structureSizeBytes_ = 0;

		for (unsigned int i = 0; i < structureFields_.size(); i++) {
			structureSizeBytes_ +=
					structureFields_[i]->getType()->getElementSize();
		}

	}

	return structureSizeBytes_;
}

bool VMEntryType::isReference() {
	return reference_;
}

SmartPointer<VMEntryType> VMEntryType::arraySubtype() {
	return arraySubtype_;
}

std::string VMEntryType::debugType() {

	std::string res = "Name: " + name_ + " ";

	if (reference_) {
		res += "is a reference ";
	}

	if (baseType_ == VMArray) {
		res += "is an array ";
	}

	return res + "\n";
}

} /* namespace VM */
