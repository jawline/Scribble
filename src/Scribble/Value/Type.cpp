/*
 * Type.cpp
 *
 *  Created on: 13 Apr 2013
 *      Author: blake
 */

#include "Type.hpp"
#include <Scribble/Parser/TypeReference.hpp>
#include <Scribble/Function/FunctionSignature.hpp>

namespace ScribbleCore {

Type::Type(ValueType rawType, TypeReference subType) :
		rawType_(rawType), subType_(subType) {
}

Type::Type(std::vector<TypeReference> argumentTypes, TypeReference returnType) :
		rawType_(FunctionReferenceType), referenceArgumentTypes_(argumentTypes), referenceReturnType_(
				returnType) {
}

Type::~Type() {
}

bool Type::Equals(Type* other) {

	if (other == nullptr) {
		printf("Equality check on nullptr\n");
	}

	if (other->rawType_ != rawType_) {
		return false;
	}

	//TODO: Probably needs cleaning up. Sleepy

	//Check if the array is the same
	if (rawType_ == Array) {

		if (subType_.get() != nullptr) {

			if (other->subType_.get() == nullptr) {
				return false;
			}

			if (subType_->type != nullptr) {

				if (other->subType_->type == nullptr) {
					return false;
				}

				return subType_->type->Equals(other->subType_->type);
			}

			printf(
					"TODO: Subtypes %s %s have not been resolved. Find out why\n",
					subType_->name.c_str(), other->subType_->name.c_str());
			printf(
					"WARNING: Currently assuming structures with the same resolve name are referencing the same thing. Fix this\n");

			return subType_->name == other->subType_->name;
		}

	} else if (rawType_ == FunctionReferenceType) {

		if (!referenceReturnType_->type->Equals(
				other->referenceReturnType_->type)) {
			return false;
		}

		if (referenceArgumentTypes_.size()
				!= other->referenceArgumentTypes_.size()) {
			return false;
		}

		for (unsigned int i = 0; i < referenceArgumentTypes_.size(); i++) {

			if (!referenceArgumentTypes_[i]->type->Equals(
					other->referenceArgumentTypes_[i]->type)) {
				return false;
			}

		}

	} else if (rawType_ == StructureType) {

		//Structure check is overloaded in StructureInfo
		printf("ERR SHOULD NOT BE HERE\n");
		for (;;) {
		}

	}

	return true;
}

Type* Type::getSubtype() {
	return subType_->type;
}

TypeReference Type::getSubtypeReference() {
	return subType_;
}

}
