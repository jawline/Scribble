/*
 * Modulo.cpp
 *
 *  Created on: May 18, 2013
 *      Author: blake
 */

#include "Modulo.hpp"
#include <Value/TypeManager.hpp>
#include <Value/Int.hpp>
#include <Statement/Heap.hpp>

Modulo::Modulo() {
	// TODO Auto-generated constructor stub

}

Modulo::~Modulo() {
	// TODO Auto-generated destructor stub
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

void Modulo::check() {

}
