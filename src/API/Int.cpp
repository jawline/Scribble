/*
 * Int.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: blake
 */

#include "Int.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace API {

IntFromFloat32::IntFromFloat32(std::string ns) :
		Function("Int", ns) {


	std::vector<ScribbleCore::TypeReference> refs;
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::Float32)));

	ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
			ScribbleCore::getTypeManager().getType(ScribbleCore::Int));

	setSignature(ScribbleCore::FunctionSignature(refs, returnType));

}

IntFromFloat32::~IntFromFloat32() {
	// TODO Auto-generated destructor stub
}

ScribbleCore::Type* IntFromFloat32::getType() {
	return ScribbleCore::getIntType();
}

const unsigned int IntFromFloat32::numArgs() {
	return 1;
}

ScribbleCore::Type* IntFromFloat32::argType(unsigned int arg) {

	if (arg == 0) {
		return ScribbleCore::getFloat32Type();
	}

	return ScribbleCore::getTypeManager().getType(ScribbleCore::TypeUnresolved);
}

API::APIValue IntFromFloat32::execute(API::APIValue* values,
		VM::VirtualMachine* virt) {
	int val = values[0].getValueFloat32();
	return API::APIValue(ScribbleCore::getIntType(), val);
}

} /* namespace API */
