/*
 * APIFunction.cpp
 *
 *  Created on: 6 Jan 2014
 *      Author: blake
 */

#include "APIFunction.hpp"

namespace API {

APIFunction::APIFunction(std::string name, std::string package,
                         ScribbleCore::FunctionSignature sig,
                         API::APIValue (*fn)(API::APIValue*, VM::VirtualMachine* virt)) :
    Function(name, package), fn_(fn) {
    setSignature(sig);
}

APIFunction::~APIFunction() {
}

APIValue APIFunction::execute(API::APIValue* values,
                              VM::VirtualMachine* virt) {
    return fn_(values, virt);
}

} /* namespace API */
