#include "String.hpp"
#include "TypeManager.hpp"
#include <Scribble/Statement/StatementException.hpp>

StringValue::StringValue(std::string const value) {
	value_ = std::string(value);
}

void StringValue::applyOperator(ValueOperator e, Value* r) {

	StringValue* other = (StringValue*) r;

	switch (e) {

	case Assign:
		value_ = other->getValue();
		break;

	case Add:
		value_ = value_ + other->getValue();
		break;

	default:
		throw StatementException(0, "Not yet implemented");
		break;
	}

}

std::string StringValue::getValue() {
	return value_;
}

void StringValue::setValue(std::string const& ref) {
	value_ = ref;
}

Type* StringValue::type() {
	return getStringType();
}

Value* StringValue::clone() {
	StringValue* gen = (StringValue*) valueHeap.make(getStringType());
	gen->setValue(value_);
	return gen;
}
