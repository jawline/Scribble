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
	Type* subType_;

public:
	Type(ValueType rawType, Type* subType);
	virtual ~Type();

	ValueType getType() {
		return rawType_;
	}

	Type* getSubtype() {
		return subType_;
	}
};

#endif /* TYPE_HPP_ */
