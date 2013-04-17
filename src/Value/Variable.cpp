#include "Variable.hpp"

Variable::Variable(ValueType type, int position, Value* value) :
		value_(value), position_(position), type_(type) {
}

Variable::~Variable() {
	delete value_;
}

Value* Variable::getValue() {
	return value_;
}

ValueType Variable::getType() {
	return type_;
}

void Variable::setPosition(int pos) {
	position_ = pos;
}

int Variable::getPosition() {
	return position_;
}

void Variable::setType(ValueType newType) {
	type_ = newType;
}

void Variable::setValue(Value* v) {
	value_ = v;
}
