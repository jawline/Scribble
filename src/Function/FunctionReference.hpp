/*
 * FunctionReference.hpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#ifndef FUNCTIONREFERENCE_HPP_
#define FUNCTIONREFERENCE_HPP_
#include <Pointers/SmartPointer.hpp>
#include "Function.hpp"
#include <string>

class FunctionReference {
private:
	std::string name_;
	SmartPointer<Function> func_;

public:
	FunctionReference(std::string name, SmartPointer<Function> func);
	virtual ~FunctionReference();

	std::string getName() {
		return name_;
	}
	SmartPointer<Function> getFunction() {
		return func_;
	}

	void setFunction(SmartPointer<Function> func) {
		func_ = func;
	}
};

#endif /* FUNCTIONREFERENCE_HPP_ */
