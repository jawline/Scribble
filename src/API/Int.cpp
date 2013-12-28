/*
 * Int.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: blake
 */

#include "Int.hpp"
#include <Scribble/Value/Float32.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Value/TypeManager.hpp>

namespace API {

IntFromFloat32::IntFromFloat32(std::string ns) :
		Function("Int", ns) {
	// TODO Auto-generated constructor stub

}

IntFromFloat32::~IntFromFloat32() {
	// TODO Auto-generated destructor stub
}

Type* IntFromFloat32::getType() {
	return getIntType();
}

const unsigned int IntFromFloat32::numArgs() {
	return 1;
}

Type* IntFromFloat32::argType(unsigned int arg) {

	if (arg == 0) {
		return getFloat32Type();
	}

	return getTypeManager().getType(TypeUnresolved);
}

Value* IntFromFloat32::execute(std::vector<Value*> arguments) {
	Float32Value* val = (Float32Value*) arguments[0];
	return valueHeap.make((int) val->getValue());
}

API::APIValue IntFromFloat32::execute(API::APIValue* values,
		VM::VirtualMachine* virt) {
	int val = values[0].getValueFloat32();
	return API::APIValue(val);
}

} /* namespace API */
