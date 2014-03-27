/*
 * StringFunction.cpp
 *
 *  Created on: 10 Mar 2013
 *      Author: blake
 */

#include "StringFunction.hpp"
#include <Scribble/Statement/StatementException.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <sstream>

IntToStringFunction::IntToStringFunction(std::string ns) :
		Function("IntToString", ns) {


	std::vector<ScribbleCore::TypeReference> refs;
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::Int)));

	ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
			ScribbleCore::getTypeManager().getType(ScribbleCore::StringType));

	setSignature(ScribbleCore::FunctionSignature(refs, returnType));

}

IntToStringFunction::~IntToStringFunction() {
	// TODO Auto-generated destructor stub
}

ScribbleCore::Type* IntToStringFunction::getType() {
	return ScribbleCore::getStringType();
}

unsigned int const IntToStringFunction::numArgs() {
	return 1;
}

ScribbleCore::Type* IntToStringFunction::argType(unsigned int arg) {

	if (arg == 0) {
		return ScribbleCore::getIntType();
	}

	return ScribbleCore::getTypeManager().getType(ScribbleCore::TypeUnresolved);
}

API::APIValue IntToStringFunction::execute(API::APIValue* values,
		VM::VirtualMachine* virt) {

	//Get the number to convert to a string
	int toConv = values[0].getValue32();

	//Create a string stream to convert the integer to a string
	std::stringstream res;
	res << toConv;

	//Get the resulting string
	std::string resultString = res.str();

	return API::APIValue::makeString(resultString, virt);
}

BoolToStringFunction::BoolToStringFunction(std::string ns) :
		Function("BoolToString", ns) {



	std::vector<ScribbleCore::TypeReference> refs;
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::Boolean)));

	ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
			ScribbleCore::getTypeManager().getType(ScribbleCore::StringType));

	setSignature(ScribbleCore::FunctionSignature(refs, returnType));
}

BoolToStringFunction::~BoolToStringFunction() {
	// TODO Auto-generated destructor stub
}

ScribbleCore::Type* BoolToStringFunction::getType() {
	return ScribbleCore::getStringType();
}

unsigned int const BoolToStringFunction::numArgs() {
	return 1;
}

ScribbleCore::Type* BoolToStringFunction::argType(unsigned int arg) {

	if (arg == 0) {
		return ScribbleCore::getBooleanType();
	}

	return ScribbleCore::getTypeManager().getType(ScribbleCore::TypeUnresolved);
}

API::APIValue BoolToStringFunction::execute(API::APIValue* values,
		VM::VirtualMachine* virt) {

	if (values[0].getValueBoolean()) {
		return API::APIValue::makeString("true", virt);
	}

	return API::APIValue::makeString("false", virt);
}

Float32ToStringFunction::Float32ToStringFunction(std::string ns) :
		Function("BoolToString", ns) {


	std::vector<ScribbleCore::TypeReference> refs;
	refs.push_back(
			ScribbleCore::makeTypeReference(
					ScribbleCore::getTypeManager().getType(
							ScribbleCore::Float32)));

	ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
			ScribbleCore::getTypeManager().getType(ScribbleCore::StringType));

	setSignature(ScribbleCore::FunctionSignature(refs, returnType));

}

Float32ToStringFunction::~Float32ToStringFunction() {
	// TODO Auto-generated destructor stub
}

ScribbleCore::Type* Float32ToStringFunction::getType() {
	return ScribbleCore::getStringType();
}

unsigned int const Float32ToStringFunction::numArgs() {
	return 1;
}

ScribbleCore::Type* Float32ToStringFunction::argType(unsigned int arg) {

	if (arg == 0) {
		return ScribbleCore::getFloat32Type();
	}

	return ScribbleCore::getTypeManager().getType(ScribbleCore::TypeUnresolved);
}

API::APIValue Float32ToStringFunction::execute(API::APIValue* values,
		VM::VirtualMachine* virt) {

	//Get the floating point value to convert
	float32_t val = values[0].getValueFloat32();

	//Use a string stream to convert it to a string
	std::stringstream res;
	res << val;

	std::string resultString = res.str();

	//Return a new API string from the resulting string
	return API::APIValue::makeString(resultString, virt);
}

StringCompare::StringCompare(std::string ns) :
		Function("StringCompare", ns) {


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

StringCompare::~StringCompare() {

}

API::APIValue StringCompare::execute(API::APIValue* values,
		VM::VirtualMachine* virt) {
	return API::APIValue::makeInt32(
			strcmp(values[0].getValueString(), values[1].getValueString()));
}

ScribbleCore::Type* StringCompare::getType() {
 return ScribbleCore::getIntType();
}

const unsigned int StringCompare::numArgs() {
 return 2;
}

ScribbleCore::Type* StringCompare::argType(unsigned int arg) {

 if (arg < 2) {
  return ScribbleCore::getStringType();
 }

 return nullptr;
}
