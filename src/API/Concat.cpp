/*
 * Concat.cpp
 *
 *  Created on: 20 Sep 2013
 *      Author: blake
 */

#include "Concat.hpp"
#include <Scribble/Value/String.hpp>
#include <Scribble/Value/TypeManager.hpp>

namespace API {

Concat::Concat(std::string ns) :
		Function("StringConcat", ns) {
	// TODO Auto-generated constructor stub

}

Concat::~Concat() {
	// TODO Auto-generated destructor stub
}

Type* Concat::getType() {
	return getTypeManager().getType(String);
}

const unsigned int Concat::numArgs() {
	return 2;
}

Type* Concat::argType(unsigned int arg) {
	return getTypeManager().getType(String);
}

Value* Concat::execute(std::vector<Value*> arguments) {
	return new StringValue(
			((StringValue*) arguments[0])->getValue()
					+ ((StringValue*) arguments[1])->getValue());
}

API::APIValue Concat::execute(API::APIValue* values, VM::VirtualMachine* virt) {

	char* lhs = values[0].getValueString();
	char* rhs = values[1].getValueString();

	if (lhs == nullptr || rhs == nullptr) {

		virt->printState();

		printf("Concat FCall Error\n");

		for (;;) {
		}

	}

	std::string result = std::string(lhs) + std::string(rhs);

	return API::APIValue::makeString(result, virt);
}

} /* namespace API */
