/*
 * Type.cpp
 *
 *  Created on: 13 Apr 2013
 *      Author: blake
 */

#include "Type.hpp"
#include <Scribble/Parser/TypeReference.hpp>

Type::Type(ValueType rawType, TypeReference subType) :
		rawType_(rawType), subType_(subType) {

}

Type::~Type() {
}

bool Type::Equals(Type* other) {

	if (other->rawType_ != rawType_) {
		return false;
	}

	//TODO: Probably needs cleaning up. Sleepy

	if (!subType_.Null()) {

		if (other->subType_.Null()) {
			return false;
		}

		if (subType_->type == nullptr && other->subType_->type != nullptr) {
			return false;
		}

		if (subType_->type != nullptr) {

			if (other->subType_->type == nullptr) {
				return false;
			}

			return subType_->type->Equals(other->subType_->type);
		}

		return subType_->name == other->subType_->name;
		//return subType_->Equals(other->subType_);
	}

	return true;
}

Type* Type::getSubtype() {
	return subType_->type;
}

TypeReference Type::getSubtypeReference() {
	return subType_;
}
