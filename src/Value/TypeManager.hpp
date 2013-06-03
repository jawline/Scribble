/*
 * TypeManager.hpp
 *
 *  Created on: 22 Apr 2013
 *      Author: blake
 */

#ifndef TYPEMANAGER_HPP_
#define TYPEMANAGER_HPP_
#include "Type.hpp"
#include <vector>

/**
 * Class used to ensure that only one of every type is created
 * ( And therefore the pointers will alyways be to that type and unique to that type).
 */
class TypeManager {
private:
	std::vector<Type*> types_;

	Type* tFind(Type* desired);

public:
	TypeManager();
	virtual ~TypeManager();

	/**
	 * Get a given primitive type (Int, Bool, etc)
	 */
	Type* getType(ValueType base);

	/**
	 * Get a given complex type. (Array, Reference)
	 */
	Type* getType(ValueType base, TypeReference subType);
};

TypeManager& getTypeManager();
Type* getStringType();
Type* getIntType();
Type* getBooleanType();
Type* getVoidType();

#endif /* TYPEMANAGER_HPP_ */
