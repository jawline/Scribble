/*
 * FunctionSignature.cpp
 *
 *  Created on: 26 Mar 2014
 *      Author: blake
 */

#include "FunctionSignature.hpp"

namespace ScribbleCore {

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

bool FunctionSignature::argumentsEqual(std::vector<Type*> args) {

    if (arguments_.size() != args.size()) {
        return false;
    }

    for (unsigned int i = 0; i < args.size(); i++) {

        if (args[i] == nullptr || arguments_[i].get() == nullptr || arguments_[i]->type() == nullptr) {
            printf("Error. Function Signature cannot evaluate nullptr\n");
            return false;
        }

        if (!args[i]->Equals(arguments_[i]->type())) {
            return false;
        }

    }

    return true;
}

bool FunctionSignature::equalTo(FunctionSignature other) {

    if (getArguments().size() != other.getArguments().size()) {
        return false;
    }

    for (unsigned int i = 0; i < getArguments().size(); i++) {

        if (!getArguments()[i]->type()->Equals(other.getArguments()[i]->type())) {
            return false;
        }

    }

    if (!getReturnType()->type()->Equals(other.getReturnType()->type())) {
        return false;
    }

    return true;
}


} /* namespace ScribbleCore */
