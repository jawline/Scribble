/*
 * Type.hpp
 *
 *  Created on: 13 Apr 2013
 *      Author: blake
 */

#ifndef TYPE_HPP_
#define TYPE_HPP_
#include <Pointers/SmartPointer.hpp>
#include <VM/VMEntryType.hpp>

namespace ScribbleCore {

class TypeReferenceCore;

/**
 * The TypeReference class is a reference counted pointer to a reference of a type. This is used
 * because the compiler allows for the use of types before they are defined. These references are
 * resolved after the packages are parsed and allow the linking between a reference to a type and
 * its defined type.
 */

typedef SmartPointer<TypeReferenceCore> TypeReference;

/**
 * The value operator is an enum that defines the basic operations that can be
 * applied to a numeric value.
 */

enum ValueOperator {
	Add, Subtract, Divide, Multiply
};

/**
 *  Enum defining variable types (Integer, Boolean, Etcetera)
 */

enum ValueType {

	/**
	 * Unresolved type used during parsing when a function call, variable type etc has not yet been inferred.
	 */

	TypeUnresolved = -1,

	/**
	 * String type, represented by std::string. n bytes
	 */

	StringType = 0,

	/**
	 * 1 byte booleans.
	 */

	Boolean,

	/**
	 * Integer numbers. Stored as 4 byte signed integers.
	 */

	Int,

	/**
	 * 32 bit floating point numbers.
	 */

	Float32,

	/**
	 * Void type - Carries no data
	 */

	Void,

	/**
	 * Nil Type, Only auto cast type. Is equivilent to any other types initial state ( nilptr for references, 0 for numbers, false for booleans )
	 */

	NilType,

	/**
	 * Primitive array type, always grouped with a subtype used to tell what it is an array of.
	 */

	Array,

	/**
	 * Structure type. Subtype will be StructureInfo
	 */

	StructureType,

	FunctionReferenceType,

	/**
	 * Max hint used so that heaps can allocate arrays of the correct number of buckets.
	 */

	ValueTypeMax
};

/**
 * The class type represents a data type within the language.
 * For instance array(int) would be a unique type represented by Type ( primtive:array, subtype: Type(primitive:int) )
 */

class Type {
private:

	/**
	 * The raw primitive type (Array, Int, Void, etc)
	 */

	ValueType rawType_;

	/**
	 * The sub type of this type. Only applicable to arrays & references.
	 */

	TypeReference subType_;

	std::vector<TypeReference> referenceArgumentTypes_;
	TypeReference referenceReturnType_;

public:

	/**
	 * Create a new type with a given primitive type and subtype (Subtype null if type has no subtype).
	 */

	Type(ValueType rawType, TypeReference subType);
	Type(std::vector<TypeReference> argumentTypes, TypeReference returnType);

	virtual ~Type();

	/**
	 * Get this types primitive type.
	 */

	ValueType getType() {
		return rawType_;
	}

	/**
	 * Returns true if the value is a primitive type that fits into a register.
	 */

	bool isPrimitive() {

		switch (rawType_) {
		case ValueType::StringType:
		case ValueType::Array:
		case ValueType::StructureType:
			return false;

		default:
			return true;
		}

	}

	/**
	 * Get this types subtype.
	 */

	Type* getSubtype();

	/**
	 * Test whether this type is equivalent to a given type.
	 */
	virtual bool Equals(Type* other);

	/**
	 * If this type is an array then this will return a reference to its subtype.
	 */

	TypeReference getSubtypeReference();

	/**
	 * Get the human readable name of this type.
	 */

	virtual std::string getTypeName() {

		switch (getType()) {
		case Array: {
			if (getSubtype() != nullptr) {
				return std::string("array(") + getSubtype()->getTypeName() + ")";
			} else {
				return "array(unresolved-type)";
			}
		}
		case StructureType:
			//StructureType overrides getTypeName. This should never execute.
			return "INVALID-SHOULD-HAVE-BEEN-OVERWRITTEN";
		case ValueType::Int:
			return "int";
		case ValueType::Boolean:
			return "bool";
		case ValueType::StringType:
			return "string";
		case ValueType::Void:
			return "void";
		case ValueType::NilType:
			return "nil";
		case ValueType::Float32:
			return "float32";
		case ValueType::TypeUnresolved:
			return "unresolved-type";
		case ValueType::ValueTypeMax:
		default:
			return "invalid";
		}

	}

};

}

#endif /* TYPE_HPP_ */
