/*
 * Pow.cpp
 *
 *  Created on: 21 Nov 2013
 *      Author: blake
 */

#include "Pow.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <math.h>       /* pow */

namespace API {

Pow::Pow(std::string ns) :
		Function("PowIntToInt", ns) {


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

Pow::~Pow() {
}

APIValue Pow::execute(API::APIValue* values, VM::VirtualMachine* virt) {
	return API::APIValue(ScribbleCore::getIntType(), pow(values[0].getValue32(), (int) values[1].getValue32()));
}
PowFloat32::PowFloat32(std::string ns) :
		Function("PowFloat32ToFloat32", ns) {


	std::vector<ScribbleCore::TypeReference> refs;
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::Float32)));
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::Float32)));

	ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
			ScribbleCore::getTypeManager().getType(ScribbleCore::Float32));

	setSignature(ScribbleCore::FunctionSignature(refs, returnType));

}

PowFloat32::~PowFloat32() {
}

APIValue PowFloat32::execute(API::APIValue* values, VM::VirtualMachine* virt) {

	float32_t left = values[0].getValueFloat32();
	float32_t right = values[1].getValueFloat32();

	float32_t power = pow(left, right);

	return API::APIValue::makeFloat32(power);
}


} /* namespace API */
