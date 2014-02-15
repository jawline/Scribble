#include "Variable.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

Variable::Variable(int position, TypeReference type) :
		type_(type), position_(position) {
}

Variable::~Variable() {

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

void Variable::setType(Type* type) {

	if (type_.get() == nullptr) {
		type_ = TypeReference(new TypeReferenceCore("", type));
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
