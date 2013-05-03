#include "Int.hpp"
#include <Statement/StatementException.hpp>
#include "TypeManager.hpp"

void IntValue::applyOperator(ValueOperator v, Value* r) {
	IntValue* other = (IntValue*) r;

	switch (v) {

	case Assign:
		value_ = other->value();
		break;

	case Add:
		value_ = value_ + other->value();
		break;

	case Subtract:
		value_ -= other->value();
		break;

	case Multiply:
		value_ *= other->value();
		break;

	case Divide:
		value_ /= other->value();
		break;

	default:
		throw StatementException(0, "Not implemented yet");
		break;
	}
}

Type* IntValue::type() {
	return getIntType();
}

int IntValue::value() {
	return value_;
}

void IntValue::setValue(int v) {
	value_ = v;
}

Value* IntValue::clone() {
	return valueHeap.make(value_);
}
