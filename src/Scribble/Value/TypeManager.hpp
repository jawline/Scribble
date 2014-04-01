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

namespace ScribbleCore {

/**
 * Class used to ensure that only one of every type is created
 * ( And therefore the pointers will alyways be to that type and unique to that type).
 * Structures are generated at the end of a parse and not on demand and thus are not involved with this class.
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

	Type* getType(std::vector<TypeReference> argumentTypes, TypeReference returnType);
};

/**
 * Return a pointer to a singleton type manager which can return pointers to base and array types ( Structures are generated at the end of a parse and not on demand ).
 */

TypeManager& getTypeManager();

Type* getStringType();

/**
 * Return a pointer to the int type singleton.
 */

Type* getIntType();

/**
 * Return a pointer to the boolean type singleton.
 */

Type* getBooleanType();

/**
 * Return a pointer to the void type singleton.
 */

Type* getVoidType();

/**
 * Return a pointer to the float32 type singleton.
 */

Type* getFloat32Type();

/**
 * Return a pointer to the nil type singleton.
 */

Type* getNilType();

}

#endif /* TYPEMANAGER_HPP_ */
