/*
 * Pow.cpp
 *
 *  Created on: 21 Nov 2013
 *      Author: blake
 */

#include "Pow.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Value/Int.hpp>
#include <Scribble/Value/Float32.hpp>
#include <Scribble/Statement/Heap.hpp>
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
	return API::APIValue(pow(values[0].getValue32(), (int) values[1].getValue32()));
}

Value* Pow::execute(std::vector<Value*> arguments) {

	IntValue* lhs = (IntValue*) arguments[0];
	IntValue* rhs = (IntValue*) arguments[1];

	int mod = pow(lhs->value(), rhs->value());

	return valueHeap.make(mod);
}

Type* Pow::getType() {
	return getIntType();
}

const unsigned int Pow::numArgs() {
	return 2;
}

Type* Pow::argType(unsigned int arg) {

	if ((arg == 0) || (arg == 1)) {
		return getIntType();
	}

	return getTypeManager().getType(TypeUnresolved);
}

PowFloat32::PowFloat32(std::string ns) :
		Function("PowFloat32ToFloat32", ns) {
	// TODO Auto-generated constructor stub

}

PowFloat32::~PowFloat32() {
	// TODO Auto-generated destructor stub
}

APIValue PowFloat32::execute(API::APIValue* values, VM::VirtualMachine* virt) {

	int64_t left = values[0].getValue32();
	int64_t right = values[1].getValue32();

	float32_t power = pow(*((float32_t*) &left), *((float32_t*) &right));

	return API::APIValue(*((long*) &power));
}

Value* PowFloat32::execute(std::vector<Value*> arguments) {

	Float32Value* lhs = (Float32Value*) arguments[0];
	Float32Value* rhs = (Float32Value*) arguments[1];

	float32_t mod = pow(lhs->getValue(), rhs->getValue());

	return valueHeap.make(mod);
}

Type* PowFloat32::getType() {
	return getFloat32Type();
}

const unsigned int PowFloat32::numArgs() {
	return 2;
}

Type* PowFloat32::argType(unsigned int arg) {

	if ((arg == 0) || (arg == 1)) {
		return getFloat32Type();
	}

	return getTypeManager().getType(TypeUnresolved);
}

} /* namespace API */
