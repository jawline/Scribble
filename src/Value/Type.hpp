/*
 * Type.hpp
 *
 *  Created on: 13 Apr 2013
 *      Author: blake
 */

#ifndef TYPE_HPP_
#define TYPE_HPP_
#include <Pointers/SmartPointer.hpp>

// Enum defining variable types (Integer, Boolean, Etcetera)
enum ValueType {
	TypeUnresolved = -1,
	String = 0,
	Boolean = 1,
	Int = 2,
	Void = 3,
	Array = 4,
	ValueTypeMax = 5
};

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

	bool Equals(Type const* other);
};

#endif /* TYPE_HPP_ */
