#include "Variable.hpp"
#include <Scribble/Value/TypeManager.hpp>

Variable::Variable(int position, TypeReference type, Value* value) :
		value_(value), type_(type), position_(position) {
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

	if (!type_.Null() && type_->type != nullptr) {
		return type_->type;
	}

	/**
	if (getValue()) {
		return getValue()->type();
	}*/

	return getTypeManager().getType(TypeUnresolved);
}

void Variable::setType(Type* type) {

	if (type_.Null()) {
		type_ = TypeReference ( new TypeReferenceCore( "", type) );
	} else {
		type_->type = type;
	}

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
