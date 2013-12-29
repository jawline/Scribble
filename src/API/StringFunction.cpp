/*
 * StringFunction.cpp
 *
 *  Created on: 10 Mar 2013
 *      Author: blake
 */

#include "StringFunction.hpp"
#include <Scribble/Statement/StatementException.hpp>
#include <Scribble/Value/Int.hpp>
#include <Scribble/Value/Bool.hpp>
#include <Scribble/Value/String.hpp>
#include <Scribble/Value/Float32.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <sstream>

IntToStringFunction::IntToStringFunction(std::string ns) :
		Function("IntToString", ns) {
	// TODO Auto-generated constructor stub

}

IntToStringFunction::~IntToStringFunction() {
	// TODO Auto-generated destructor stub
}

Value* IntToStringFunction::execute(std::vector<Value*> arguments) {
	Value* arg = arguments[0];
	std::stringstream st;

	st << ((IntValue*) arg)->value();

	return new StringValue(st.str());
}

Type* IntToStringFunction::getType() {
	return getTypeManager().getType(String);
}

unsigned int const IntToStringFunction::numArgs() {
	return 1;
}

Type* IntToStringFunction::argType(unsigned int arg) {

	if (arg == 0) {
		return getTypeManager().getType(Int);
	}

	return getTypeManager().getType(TypeUnresolved);
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
	// TODO Auto-generated constructor stub

}

BoolToStringFunction::~BoolToStringFunction() {
	// TODO Auto-generated destructor stub
}

Value* BoolToStringFunction::execute(std::vector<Value*> arguments) {
	Value* arg = arguments[0];
	std::stringstream st;

	if (((BoolValue*) arg)->value()) {
		st << "true";
	} else {
		st << "false";
	}

	return new StringValue(st.str());
}

Type* BoolToStringFunction::getType() {
	return getTypeManager().getType(String);
}

unsigned int const BoolToStringFunction::numArgs() {
	return 1;
}

Type* BoolToStringFunction::argType(unsigned int arg) {

	if (arg == 0) {
		return getTypeManager().getType(Boolean);
	}

	return getTypeManager().getType(TypeUnresolved);
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
	// TODO Auto-generated constructor stub

}

Float32ToStringFunction::~Float32ToStringFunction() {
	// TODO Auto-generated destructor stub
}

Value* Float32ToStringFunction::execute(std::vector<Value*> arguments) {
	Value* arg = arguments[0];
	std::stringstream st;
	st << ((Float32Value*) arg)->getValue();
	return new StringValue(st.str());
}

Type* Float32ToStringFunction::getType() {
	return getTypeManager().getType(String);
}

unsigned int const Float32ToStringFunction::numArgs() {
	return 1;
}

Type* Float32ToStringFunction::argType(unsigned int arg) {

	if (arg == 0) {
		return getTypeManager().getType(Float32);
	}

	return getTypeManager().getType(TypeUnresolved);
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
