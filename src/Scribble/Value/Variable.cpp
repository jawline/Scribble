#include "Variable.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

Variable::Variable(std::string name, int position, TypeReference type) :
    name_(name), type_(type), position_(position) {
}

Variable::~Variable() {

}

std::string Variable::getName() const {
    return name_;
}

Type* Variable::getType() const {

    if (type_.get() != nullptr && type_->type() != nullptr) {
        return type_->type();
    }

    /**
     if (getValue()) {
     return getValue()->type();
     }*/

    return getTypeManager().getType(TypeUnresolved);
}

TypeReference Variable::getTypeReference() const {
    return type_;
}

void Variable::setType(Type* type) {
    type_->setType(type);
}

void Variable::setPosition(int pos) {
    position_ = pos;
}

int Variable::getPosition() const {
    return position_;
}

}
