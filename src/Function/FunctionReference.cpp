/*
 * FunctionReference.cpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#include "FunctionReference.hpp"

FunctionReference::FunctionReference(std::string fnNamespace, std::string name,
		std::vector<SafeStatement> fnArgs, SmartPointer<Function> func) {
	name_ = name;
	fnNamespace_ = fnNamespace;
	fnArgs_ = fnArgs;
	func_ = func;
}

FunctionReference::~FunctionReference() {
	// TODO Auto-generated destructor stub
}

std::string FunctionReference::getDebugName() {
	if (getNamespace().size() > 0) {
		return getNamespace() + "." + getName();
	} else {
		return getName();
	}
}

std::vector<SafeStatement> const& FunctionReference::getArgs() {
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
