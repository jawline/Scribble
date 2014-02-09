/*
 * Float.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: blake
 */

#include "Float.hpp"
#include <Scribble/Value/Float32.hpp>
#include <Scribble/Value/Int.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <types.h>

namespace API {

Float32FromInt::Float32FromInt(std::string ns) : Function("Float", ns) {
	// TODO Auto-generated constructor stub

}

Float32FromInt::~Float32FromInt() {
	// TODO Auto-generated destructor stub
}

API::APIValue Float32FromInt::execute(API::APIValue* values,
		VM::VirtualMachine* virt) {
	return API::APIValue(getIntType(), values[0].getValueFloat32());
}

Type* Float32FromInt::getType() {
	return getFloat32Type();
}

const unsigned int Float32FromInt::numArgs() {
	return 1;
}

Type* Float32FromInt::argType(unsigned int arg) {

	if (arg == 0) {
		return getIntType();
	}

	return getTypeManager().getType(TypeUnresolved);
}

} /* namespace API */
