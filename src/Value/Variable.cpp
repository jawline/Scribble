#include "Variable.hpp"

Variable::Variable(ValueType type, Value* value) {
	type_ = type;
	value_ = value;
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
