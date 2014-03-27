/*
 * FunctionSignature.cpp
 *
 *  Created on: 26 Mar 2014
 *      Author: blake
 */

#include "FunctionSignature.hpp"

namespace ScribbleCore {

FunctionSignature::FunctionSignature() {

}

FunctionSignature::FunctionSignature(std::vector<TypeReference> args, TypeReference returnType) : arguments_(args), returnType_(returnType) {
}

FunctionSignature::~FunctionSignature() {
}

std::vector<TypeReference> FunctionSignature::getArguments() {
 return arguments_;
}

TypeReference FunctionSignature::getReturnType() {
 return returnType_;
}

bool FunctionSignature::equalTo(FunctionSignature& other) {

	if (!returnType_->type->Equals(other.getReturnType()->type)) {
		return false;
	}

	if (getArguments().size() != other.getArguments().size()) {
		return false;
	}

	for (unsigned int i = 0; i < getArguments().size(); i++) {

		if (!getArguments()[i]->type->Equals(other.getArguments()[i]->type)) {
			return false;
		}

	}

	return true;
}

} /* namespace ScribbleCore */
