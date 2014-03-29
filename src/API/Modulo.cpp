/*
 * Modulo.cpp
 *
 *  Created on: May 18, 2013
 *      Author: blake
 */

#include "Modulo.hpp"
#include <Scribble/Value/TypeManager.hpp>

Modulo::Modulo(std::string names) : Function("NativeModulo", names) {


	std::vector<ScribbleCore::TypeReference> refs;
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::Int)));
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::Int)));

	ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
			ScribbleCore::getTypeManager().getType(ScribbleCore::Int));

	setSignature(ScribbleCore::FunctionSignature(refs, returnType));

}

Modulo::~Modulo() {
	// TODO Auto-generated destructor stub
}

APIValue Modulo::execute(API::APIValue* values, VM::VirtualMachine* virt) {
	return API::APIValue(ScribbleCore::getIntType(), values[0].getValue32() % values[1].getValue32());
}
