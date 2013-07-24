/*
 * VMEntryType.cpp
 *
 *  Created on: Jul 21, 2013
 *      Author: blake
 */

#include "VMEntryType.hpp"
#include <stdio.h>

namespace VM {

VMEntryType::VMEntryType(std::string name, bool reference) :
		name_(name), reference_(reference), array_(false) {

}

VMEntryType::VMEntryType(std::string name, SP<VMEntryType> subtype) :
		name_(name), reference_(true), array_(true), subtype_(subtype) {
}

VMEntryType::~VMEntryType() {
	// TODO Auto-generated destructor stub
}

std::string VMEntryType::typeName() {
	return name_;
}

bool VMEntryType::isReference() {
	return reference_;
}

bool VMEntryType::isArray() {
	return array_;
}

SP<VMEntryType> VMEntryType::arraySubtype() {
	return subtype_;
}

} /* namespace VM */
