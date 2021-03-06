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
}

VMFunc::VMFunc(std::string name, SmartPointer<Function> func) :
    name_(name), func_(func) {
}

VMFunc::~VMFunc() {
}

bool VMFunc::isNative() {

    if (func_ == nullptr) {
        return false;
    }

    return true;
}

} /* namespace VM */
