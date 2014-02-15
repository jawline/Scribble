/*
 * Pow.cpp
 *
 *  Created on: 21 Nov 2013
 *      Author: blake
 */

#include "Pow.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <math.h>       /* pow */

namespace API {

Pow::Pow(std::string ns) :
		Function("PowIntToInt", ns) {
	// TODO Auto-generated constructor stub

}

Pow::~Pow() {
	// TODO Auto-generated destructor stub
}

APIValue Pow::execute(API::APIValue* values, VM::VirtualMachine* virt) {
	return API::APIValue(ScribbleCore::getIntType(), pow(values[0].getValue32(), (int) values[1].getValue32()));
}

ScribbleCore::Type* Pow::getType() {
	return ScribbleCore::getIntType();
}

const unsigned int Pow::numArgs() {
	return 2;
}

ScribbleCore::Type* Pow::argType(unsigned int arg) {

	if ((arg == 0) || (arg == 1)) {
		return ScribbleCore::getIntType();
	}

	return ScribbleCore::getTypeManager().getType(ScribbleCore::TypeUnresolved);
}

PowFloat32::PowFloat32(std::string ns) :
		Function("PowFloat32ToFloat32", ns) {
	// TODO Auto-generated constructor stub

}

PowFloat32::~PowFloat32() {
	// TODO Auto-generated destructor stub
}

APIValue PowFloat32::execute(API::APIValue* values, VM::VirtualMachine* virt) {

	float32_t left = values[0].getValueFloat32();
	float32_t right = values[1].getValueFloat32();

	float32_t power = pow(left, right);

	return API::APIValue::makeFloat32(power);
}

ScribbleCore::Type* PowFloat32::getType() {
	return ScribbleCore::getFloat32Type();
}

const unsigned int PowFloat32::numArgs() {
	return 2;
}

ScribbleCore::Type* PowFloat32::argType(unsigned int arg) {

	if ((arg == 0) || (arg == 1)) {
		return ScribbleCore::getFloat32Type();
	}

	return ScribbleCore::getTypeManager().getType(ScribbleCore::TypeUnresolved);
}

} /* namespace API */
