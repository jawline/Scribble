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
		name_(name), size_(size), reference_(reference), baseType_(VMPrimitive) {

}

VMEntryType::VMEntryType(std::string name, SP<VMEntryType> subtype) :
name_(name), size_(8), reference_(true), baseType_(VMArray), arraySubtype_(subtype) {
}


VMEntryType::VMEntryType(std::string name, std::vector<SP<VMStructureField>> fields) : name_(name), size_(8), reference_(true), baseType_(VMStructure) {

	for (unsigned int i = 0; i < fields.size(); i++) {
		structureFields_.push_back(fields[i]);
	}

}

VMEntryType::~VMEntryType() {
	// TODO Auto-generated destructor stub
}

std::string VMEntryType::typeName() {
	return name_;
}

unsigned int VMEntryType::getElementSize() {
	return size_;
}

bool VMEntryType::isReference() {
	return reference_;
}

SP<VMEntryType> VMEntryType::arraySubtype() {
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
