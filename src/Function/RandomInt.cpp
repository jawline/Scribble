/*
 * RandomInt.cpp
 *
 *  Created on: 18 Mar 2013
 *      Author: blake
 */

#include "RandomInt.hpp"
#include <Value/Int.hpp>
#include <stdlib.h>     /* srand, rand */

RandomInt::RandomInt() {
}

RandomInt::~RandomInt() {
	// TODO Auto-generated destructor stub
}

Value* RandomInt::execute(std::vector<Value*> arguments) {
	return new IntValue(rand() % (((IntValue*) arguments[0])->value() + 1));
}

const ValueType RandomInt::getType() {
	return Int;
}

const unsigned int RandomInt::numArgs() {
	return 1;
}

const ValueType RandomInt::argType(int arg) {
	return Int;
}

void RandomInt::check() {
}
