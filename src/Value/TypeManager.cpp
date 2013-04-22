/*
 * TypeManager.cpp
 *
 *  Created on: 22 Apr 2013
 *      Author: blake
 */

#include "TypeManager.hpp"
#include <stdio.h>

Type* TypeManager::tFind(ValueType sType, Type* sSubType) {

	for (unsigned int i = 0; i < types_.size(); ++i) {

		if (types_[i]->getType() == sType
				&& types_[i]->getSubtype() == sSubType) {
			return types_[i];
		}

	}

	return nullptr;
}

TypeManager::TypeManager() {
	// TODO Auto-generated constructor stub

}

TypeManager::~TypeManager() {

	for (unsigned int i = 0; i < types_.size(); ++i) {
		delete types_[i];
	}

}

Type* TypeManager::getType(ValueType base) {
	return getType(base, nullptr);
}

Type* TypeManager::getType(ValueType base, Type* subType) {

	Type* found = tFind(base, subType);

	if (found != nullptr) {
		printf("Found existing type\n");
		return found;
	}

	printf("Generating new type\n");
	found = new Type(base, subType);
	types_.push_back(found);
	return found;
}
