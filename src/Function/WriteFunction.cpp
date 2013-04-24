#include "WriteFunction.hpp"
#include <stdio.h>
#include <Statement/StatementException.hpp>
#include <Value/String.hpp>
#include <Value/Void.hpp>
#include <Value/TypeManager.hpp>

Value* WriteFunction::execute(std::vector<Value*> arguments) {
	printf("%s", ((StringValue*) arguments[0])->getValue().c_str());
	return valueHeap.make(getVoidType());
}

Type* WriteFunction::argType(unsigned int arg) {

	if (arg == 0) {
		return getTypeManager().getType(String);
	}

	return getTypeManager().getType(TypeUnresolved);
}

const unsigned int WriteFunction::numArgs() {
	return 1;
}

Type* WriteFunction::getType() {
	return getTypeManager().getType(Void);
}
