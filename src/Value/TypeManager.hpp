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

class TypeManager {
private:
	std::vector<Type*> types_;

	Type* tFind(ValueType sType, Type* sSubType);

public:
	TypeManager();
	virtual ~TypeManager();

	Type* getType(ValueType base);
	Type* getType(ValueType base, Type* subType);
};

TypeManager& getTypeManager();
Type* getStringType();
Type* getIntType();
Type* getBooleanType();
Type* getVoidType();

#endif /* TYPEMANAGER_HPP_ */
