/*
 * FunctionReference.cpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#include "FunctionReference.hpp"

namespace ScribbleCore {

FunctionReference::FunctionReference(std::string fnNamespace, std::string name,
		std::vector<SafeStatement> fnArgs, SmartPointer<Function> func) {

	name_ = name;
	fnNamespace_ = fnNamespace;
	func_ = func;

	for (unsigned int i = 0; i < fnArgs.size(); i++) {

		if (fnArgs[i]->type() == nullptr) {
			printf("Error: Creating a function reference with a null arg ref %s\n", fnArgs[i]->generateDebugInformation().c_str());
		}

		fnArgs_.push_back(fnArgs[i]->type());
	}

    returnType_ = makeTypeReference(getTypeManager().getType(TypeUnresolved));
}

FunctionReference::FunctionReference(std::string fnNamespace, std::string name,
		std::vector<TypeReference> fnArgs, SmartPointer<Function> func) {
	name_ = name;
	fnNamespace_ = fnNamespace;
	func_ = func;
	fnArgs_ = fnArgs;
    returnType_ = makeTypeReference(getTypeManager().getType(TypeUnresolved));
}

FunctionReference::~FunctionReference() {
}

std::string FunctionReference::getDebugName() {
	if (getNamespace().size() > 0) {
		return getNamespace() + "." + getName();
	} else {
		return getName();
	}
}

std::vector<TypeReference> const& FunctionReference::getArgTypes() {
	return fnArgs_;
}

void FunctionReference::setResolveIssue(std::string issue) {
	resolveIssue_ = issue;
}

SmartPointer<Function> FunctionReference::getFunction() {
	return func_;
}

void FunctionReference::setFunction(SmartPointer<Function> func) {
	func_ = func;
    returnType_->type = func_->getSignature().getReturnType()->type;
}

TypeReference FunctionReference::getReturnType() {
    return returnType_;
}

std::string const& FunctionReference::getName() {
	return name_;
}

std::string const& FunctionReference::getNamespace() {
	return fnNamespace_;
}

std::string const& FunctionReference::getResolveIssue() {
	return resolveIssue_;
}

std::vector<Type*> FunctionReference::getTargetArguments() {

    std::vector<Type*> args;

	for (unsigned int i = 0; i < getArgTypes().size(); i++) {

		if (getArgTypes()[i].get() == nullptr) {
			args.push_back(getTypeManager().getType(TypeUnresolved));
		} else {
	        args.push_back(getArgTypes()[i]->type);
		}

	}

    return args;
}

}
