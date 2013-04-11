#include "WriteFunction.hpp"
#include <stdio.h>
#include <Statement/StatementException.hpp>
#include <Value/String.hpp>
#include <Value/Void.hpp>

Value* WriteFunction::execute(std::vector<Value*> arguments) {
	printf("%s", ((StringValue*) arguments[0])->getValue().c_str());
	return new VoidValue();
}

const ValueType WriteFunction::argType(unsigned int arg) {

	if (arg == 0) {
		return String;
	}

	return Void;
}

const unsigned int WriteFunction::numArgs() {
	return 1;
}

const ValueType WriteFunction::getType() {
	return Void;
}
