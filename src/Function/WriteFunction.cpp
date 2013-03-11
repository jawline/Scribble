#include "WriteFunction.hpp"
#include <stdio.h>
#include <Statement/StatementException.hpp>
#include <Value/String.hpp>

Value* WriteFunction::execute(std::vector<Value*> arguments) {
	printf("%s\n", ((StringValue*)arguments[0])->getValue().c_str());
}
