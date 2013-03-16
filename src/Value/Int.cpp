#include "Int.hpp"
#include <Statement/StatementException.hpp>

void IntValue::applyOperator(ValueOperator v, Value* r) {
	IntValue* other = (IntValue*) r;

	switch (v) {

	case Assign:
		value_ = other->value();
		break;

	case Add:
		value_ = value_ + other->value();
		break;

	default:
		throw StatementException(0, "Not implemented yet");
		break;
	}
}
