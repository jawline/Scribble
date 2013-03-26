/*
 * FunctionReference.cpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#include "FunctionReference.hpp"

FunctionReference::FunctionReference(std::string fnNamespace, std::string name, SmartPointer<Function> func) {
	name_ = name;
	fnNamespace_ = fnNamespace;
	func_ = func;
}

FunctionReference::~FunctionReference() {
	// TODO Auto-generated destructor stub
}

