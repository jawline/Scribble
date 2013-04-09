/*
 * StringFunction.cpp
 *
 *  Created on: 10 Mar 2013
 *      Author: blake
 */

#include "StringFunction.hpp"
#include <Statement/StatementException.hpp>
#include <Value/Int.hpp>
#include <Value/Bool.hpp>
#include <Value/String.hpp>
#include <sstream>

IntToStringFunction::IntToStringFunction() {
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

ValueType const IntToStringFunction::getType() {
	return String;
}

unsigned int const IntToStringFunction::numArgs() {
	return 1;
}

ValueType const IntToStringFunction::argType(int arg) {

	if (arg == 0) {
		return Int;
	}

	return TypeUnresolved;
}

BoolToStringFunction::BoolToStringFunction() {
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

ValueType const BoolToStringFunction::getType() {
	return String;
}

unsigned int const BoolToStringFunction::numArgs() {
	return 1;
}

ValueType const BoolToStringFunction::argType(int arg) {

	if (arg == 0) {
		return Boolean;
	}

	return TypeUnresolved;
}
