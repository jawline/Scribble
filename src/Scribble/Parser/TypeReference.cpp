/*
 * TypeReference.cpp
 *
 *  Created on: 26 Mar 2014
 *      Author: blake
 */

#include "TypeReference.hpp"

namespace ScribbleCore {

TypeReferenceCore::TypeReferenceCore(std::string name, Type* type) {
	this->typeNamespace = "";
	this->name = name;
	this->type = type;
}

TypeReferenceCore::TypeReferenceCore(std::string ns, std::string name, Type* type) {
	this->typeNamespace = ns;
	this->name = name;
	this->type = type;
}

TypeReference makeTypeReference(Type* type) {
	return TypeReference(new TypeReferenceCore(type->getTypeName(), type));
}

}

