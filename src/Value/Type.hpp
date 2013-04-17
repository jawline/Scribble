/*
 * Type.hpp
 *
 *  Created on: 13 Apr 2013
 *      Author: blake
 */

#ifndef TYPE_HPP_
#define TYPE_HPP_
#include <Pointers/SmartPointer.hpp>
#include "Value.hpp"

class Type {
private:
	ValueType rawType_;
	SP<Type> subType_;

public:
	Type(ValueType rawType, SP<Type> subType);
	virtual ~Type();
};

#endif /* TYPE_HPP_ */
