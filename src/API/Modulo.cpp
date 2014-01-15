/*
 * Modulo.cpp
 *
 *  Created on: May 18, 2013
 *      Author: blake
 */

#include "Modulo.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Value/Int.hpp>
#include <Scribble/Statement/Heap.hpp>

Modulo::Modulo(std::string names) : Function("NativeModulo", names) {
	// TODO Auto-generated constructor stub

}

Modulo::~Modulo() {
	// TODO Auto-generated destructor stub
}

APIValue Modulo::execute(API::APIValue* values, VM::VirtualMachine* virt) {
	return API::APIValue(getIntType(), values[0].getValue32() % values[1].getValue32());
}

Value* Modulo::execute(std::vector<Value*> arguments) {

	 IntValue* lhs = (IntValue*) arguments[0];
	 IntValue* rhs = (IntValue*) arguments[1];

	 int mod = lhs->value() % rhs->value();

	 return valueHeap.make(mod);
}

Type* Modulo::getType() {
	return getIntType();
}

const unsigned int Modulo::numArgs() {
	return 2;
}

Type* Modulo::argType(unsigned int arg) {
	return getIntType();
}
