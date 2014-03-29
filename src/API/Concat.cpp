/*
 * Concat.cpp
 *
 *  Created on: 20 Sep 2013
 *      Author: blake
 */

#include "Concat.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace API {

Concat::Concat(std::string ns) :
		Function("StringConcat", ns) {

	std::vector<ScribbleCore::TypeReference> refs;
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::StringType)));
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::StringType)));

	ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
			ScribbleCore::getTypeManager().getType(ScribbleCore::StringType));

	setSignature(ScribbleCore::FunctionSignature(refs, returnType));
}

Concat::~Concat() {
	// TODO Auto-generated destructor stub
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
