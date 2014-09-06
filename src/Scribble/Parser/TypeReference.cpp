/*
 * TypeReference.cpp
 *
 *  Created on: 26 Mar 2014
 *      Author: blake
 */

#include "TypeReference.hpp"

namespace ScribbleCore {

TypeReferenceCore::TypeReferenceCore(std::string name, Type* type) :
		typeNamespace_(""), name_(name), type_(type) {
}

TypeReferenceCore::TypeReferenceCore(std::string ns, std::string name,
		Type* type) :
		typeNamespace_(ns), name_(name), type_(type) {
}

std::string TypeReferenceCore::getNamespace() const {
	return typeNamespace_;
}

std::string TypeReferenceCore::getName() const {
	return name_;
}

Type* TypeReferenceCore::type() const {
	return type_;
}

TypeReference makeTypeReference(Type* type) {
	return TypeReference(new TypeReferenceCore(type->getTypeName(), type));
}

}

