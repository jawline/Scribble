#include "String.hpp"
#include <Statement/StatementException.hpp>

void StringValue::applyOperator(ValueOperator e, Value* r) {

	StringValue* other = (StringValue*) r;

	switch (e) {

	case Assign:
		value_ = other->getValue();
		break;

	default:
		throw StatementException("Not yet implemented");
		break;
	}

}
