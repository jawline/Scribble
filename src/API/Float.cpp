/*
 * Float.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: blake
 */

#include "Float.hpp"
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
	return API::APIValue(ScribbleCore::getIntType(), values[0].getValueFloat32());
}

ScribbleCore::Type* Float32FromInt::getType() {
	return ScribbleCore::getFloat32Type();
}

const unsigned int Float32FromInt::numArgs() {
	return 1;
}

ScribbleCore::Type* Float32FromInt::argType(unsigned int arg) {

	if (arg == 0) {
		return ScribbleCore::getIntType();
	}

	return ScribbleCore::getTypeManager().getType(ScribbleCore::TypeUnresolved);
}

} /* namespace API */
