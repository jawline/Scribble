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

