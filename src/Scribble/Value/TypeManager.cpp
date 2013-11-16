/*
 * TypeManager.cpp
 *
 *  Created on: 22 Apr 2013
 *      Author: blake
 */

#include "TypeManager.hpp"
#include <stdio.h>
#include <Scribble/Parser/TypeReference.hpp>

Type* TypeManager::tFind(Type* desired) {

	for (unsigned int i = 0; i < types_.size(); ++i) {

		if (types_[i]->Equals(desired)) {
			return types_[i];
		}

	}

	return nullptr;
}

TypeManager::TypeManager() {
}

TypeManager::~TypeManager() {

	for (unsigned int i = 0; i < types_.size(); ++i) {
		delete types_[i];
	}

}

Type* TypeManager::getType(ValueType base) {
	return getType(base, TypeReference( new TypeReferenceCore("", nullptr) ) );
}

Type* TypeManager::getType(ValueType base, TypeReference subType) {

	Type* desired = new Type(base, subType);
	Type* found = tFind(desired);

	//If already exists
	if (found != nullptr) {
		delete desired;
		return found;
	}

	//Else add
	types_.push_back(desired);
	return desired;
}

TypeManager typeInstance;

TypeManager& getTypeManager() {
	return typeInstance;
}

Type* stringType = getTypeManager().getType(String);

Type* getStringType() {
	return stringType;
}

Type* intType = getTypeManager().getType(Int);

Type* getIntType() {
	return intType;
}

Type* boolType = getTypeManager().getType(Boolean);

Type* getBooleanType() {
	return boolType;
}

Type* voidType = getTypeManager().getType(Void);

Type* getVoidType() {
	return voidType;
}

Type* float32Type = getTypeManager().getType(Float32);

Type* getFloat32Type() {
	return float32Type;
}
