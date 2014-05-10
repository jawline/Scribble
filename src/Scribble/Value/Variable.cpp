#include "Variable.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

Variable::Variable(std::string name, int position, TypeReference type) :
		name_(name), type_(type), position_(position) {
}

Variable::~Variable() {

}

std::string Variable::getName() {
	return name_;
}

Type* Variable::getType() {

	if (type_.get() != nullptr && type_->type != nullptr) {
		return type_->type;
	}

	/**
	 if (getValue()) {
	 return getValue()->type();
	 }*/

	return getTypeManager().getType(TypeUnresolved);
}

TypeReference Variable::getTypeReference() {
	return type_;
}

void Variable::setType(Type* type) {

	if (type_.get() == nullptr) {
		type_->type = getTypeManager().getType(TypeUnresolved);
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

}
