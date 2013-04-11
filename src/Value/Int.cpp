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

	case Subtract:
		value_ -= other->value();
		break;

	case Multiply:
		value_ *= other->value();
		break;

	default:
		throw StatementException(0, "Not implemented yet");
		break;
	}
}

ValueType IntValue::type() {
	return Int;
}

int IntValue::value() {
	return value_;
}

void IntValue::setValue(int v) {
	value_ = v;
}

Value* IntValue::clone() {
	IntValue* gen = (IntValue*) valueHeap.make(Int);
	gen->setValue(value_);
	return gen;
}
