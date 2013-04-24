#include "Variable.hpp"
#include <Value/TypeManager.hpp>

Variable::Variable(int position, Value* value) :
		value_(value), position_(position) {
}

Variable::~Variable() {

	if (value_ != nullptr) {
		delete value_;
	}

}

Value* Variable::getValue() {
	return value_;
}

Type* Variable::getType() {

	if (getValue()) {
		return getValue()->type();
	}

	return getTypeManager().getType(TypeUnresolved);
}

void Variable::setPosition(int pos) {
	position_ = pos;
}

int Variable::getPosition() {
	return position_;
}

void Variable::setValue(Value* v) {
	value_ = v;
}
