#include "WriteFunction.hpp"
#include <stdio.h>
#include <Statement/StatementException.hpp>
#include <Value/String.hpp>

Value* WriteFunction::execute(std::vector<Value*> arguments) {

	if ( arguments.size() != 1 ) {
		throw StatementException("Error - Write expecting a single argument");
	}

	if ( arguments[0]->type() != String ) {
		throw StatementException("Error - expected string with write function");
	}

	printf("%s\n", ((StringValue*)arguments[0])->getValue().c_str());
}
