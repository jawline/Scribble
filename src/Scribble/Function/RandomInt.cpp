/*
 * RandomInt.cpp
 *
 *  Created on: 18 Mar 2013
 *      Author: blake
 */

#include "RandomInt.hpp"
#include <stdlib.h>     /* srand, rand */
#include <Scribble/Value/Int.hpp>
#include <Scribble/Value/TypeManager.hpp>

RandomInt::RandomInt(std::string ns) : Function("RandomInt", ns) {
}

RandomInt::~RandomInt() {
	// TODO Auto-generated destructor stub
}

Value* RandomInt::execute(std::vector<Value*> arguments) {
	return new IntValue(rand() % (((IntValue*) arguments[0])->value() + 1));
}

Type* RandomInt::getType() {
	return getTypeManager().getType(Int);
}

const unsigned int RandomInt::numArgs() {
	return 1;
}

Type* RandomInt::argType(unsigned int arg) {
	return getTypeManager().getType(Int);
}

void RandomInt::check() {
}
