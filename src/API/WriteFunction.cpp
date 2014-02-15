#include "WriteFunction.hpp"
#include <stdio.h>
#include <Scribble/Statement/StatementException.hpp>
#include <Scribble/Value/TypeManager.hpp>

ScribbleCore::Type* WriteFunction::argType(unsigned int arg) {

	if (arg == 0) {
		return ScribbleCore::getStringType();
	}

	return ScribbleCore::getTypeManager().getType(ScribbleCore::TypeUnresolved);
}

const unsigned int WriteFunction::numArgs() {
	return 1;
}

ScribbleCore::Type* WriteFunction::getType() {
	return ScribbleCore::getVoidType();
}
