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
