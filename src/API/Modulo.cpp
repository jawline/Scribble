/*
 * Modulo.cpp
 *
 *  Created on: May 18, 2013
 *      Author: blake
 */

#include "Modulo.hpp"
#include <Scribble/Value/TypeManager.hpp>

Modulo::Modulo(std::string names) : Function("NativeModulo", names) {
	// TODO Auto-generated constructor stub

}

Modulo::~Modulo() {
	// TODO Auto-generated destructor stub
}

APIValue Modulo::execute(API::APIValue* values, VM::VirtualMachine* virt) {
	return API::APIValue(ScribbleCore::getIntType(), values[0].getValue32() % values[1].getValue32());
}

ScribbleCore::Type* Modulo::getType() {
	return ScribbleCore::getIntType();
}

const unsigned int Modulo::numArgs() {
	return 2;
}

ScribbleCore::Type* Modulo::argType(unsigned int arg) {
	return ScribbleCore::getIntType();
}
