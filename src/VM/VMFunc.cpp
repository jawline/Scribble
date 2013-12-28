/*
 * VMFunc.cpp
 *
 *  Created on: Aug 1, 2013
 *      Author: blake
 */

#include "VMFunc.hpp"

namespace VM {

VMFunc::VMFunc(std::string name, InstructionSet instrs) :
		name_(name), instrs_(instrs), func_(nullptr) {
	// TODO Auto-generated constructor stub

}

VMFunc::VMFunc(std::string name, SmartPointer<Function> func) :
name_(name), func_(func) {

}

VMFunc::~VMFunc() {
	// TODO Auto-generated destructor stub
}

bool VMFunc::isNative() {

	if (func_ == nullptr) {
		return false;
	}

	return true;
}

} /* namespace VM */
