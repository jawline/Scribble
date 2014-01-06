/*
 * APIFunction.cpp
 *
 *  Created on: 6 Jan 2014
 *      Author: blake
 */

#include "APIFunction.hpp"

namespace API {

APIFunction::APIFunction(std::string name, std::string package, Type* returnType, std::vector<Type*> types,
		API::APIValue (*fn)(API::APIValue*, VM::VirtualMachine* virt)) : Function(name, package),
		returnType_(returnType), types_(types), fn_(fn) {
}

APIFunction::~APIFunction() {
}

} /* namespace API */
