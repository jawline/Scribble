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

namespace API {

Float32FromInt::Float32FromInt(std::string ns) : Function("Float", ns) {
	// TODO Auto-generated constructor stub

}

Float32FromInt::~Float32FromInt() {
	// TODO Auto-generated destructor stub
}

Value* Float32FromInt::execute(std::vector<Value*> arguments) {
	IntValue* arg = (IntValue*) arguments[0];
	float val = arg->value();
	return valueHeap.make(val);
}

API::APIValue Float32FromInt::execute(API::APIValue* values,
		VM::VirtualMachine* virt) {
	long returnData = 0;
	*((float32_t*)&returnData) = values[0].getValue();
	return returnData;
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

}

} /* namespace API */
