/*
 * Type.cpp
 *
 *  Created on: 13 Apr 2013
 *      Author: blake
 */

#include "Type.hpp"

Type::Type(ValueType rawType, Type* subType) :
		rawType_(rawType), subType_(subType) {

}

Type::~Type() {
}

bool Type::Equals(Type const* other) {

	if (other->rawType_ != rawType_) {
		return false;
	}

	if (subType_ != nullptr) {
		return subType_->Equals(other->subType_);
	}

	return true;
}

