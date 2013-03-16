/*
 * StringFunction.cpp
 *
 *  Created on: 10 Mar 2013
 *      Author: blake
 */

#include "StringFunction.hpp"
#include <Statement/StatementException.hpp>
#include <Value/Int.hpp>
#include <Value/String.hpp>
#include <sstream>

StringFunction::StringFunction() {
	// TODO Auto-generated constructor stub

}

StringFunction::~StringFunction() {
	// TODO Auto-generated destructor stub
}

Value* StringFunction::execute(std::vector<Value*> arguments) {

	Value* arg = arguments[0];
	int iVal;
	std::stringstream st;

	switch (arg->type()) {

	case Int:

		iVal = ((IntValue*) arg)->value();
		st << iVal;
		return new StringValue(st.str());

	default:
		throw StatementException(0, "Cannot convert type");
		break;
	}

	return 0;
}
