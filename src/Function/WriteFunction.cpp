#include "WriteFunction.hpp"
#include <stdio.h>
#include <Statement/StatementException.hpp>
#include <Value/String.hpp>
#include <Value/Void.hpp>

Value* WriteFunction::execute(std::vector<Value*> arguments) {
	printf("%s", ((StringValue*)arguments[0])->getValue().c_str());
	return new VoidValue();
}
