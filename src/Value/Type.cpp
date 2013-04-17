/*
 * Type.cpp
 *
 *  Created on: 13 Apr 2013
 *      Author: blake
 */

#include "Type.hpp"

Type::Type(ValueType rawType, SP<Type> subType) :
		rawType_(rawType), subType_(subType) {

}

Type::~Type() {
}

