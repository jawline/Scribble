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

class TypeReferenceCore;
typedef SP<TypeReferenceCore> TypeReference;

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
	String = 0,

	/**
	 * 1 byte booleans.
	 */
	Boolean = 1,

	/**
	 * Integer numbers. Stored as 4 byte signed integers.
	 */
	Int = 2,

	/**
	 * Void type, Null type.
	 */
	Void = 3,

	/**
	 * Primitive array type, always grouped with a subtype used to tell what it is an array of.
	 */
	Array = 4,

	/**
	 * Structure type. Subtype will be StructureInfo
	 */
	StructureType = 5,

	/**
	 * Max hint used so that heaps can allocate arrays of the correct number of buckets.
	 */
	ValueTypeMax = 7
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

public:

	/**
	 * Create a new type with a given primitive type and subtype (Subtype null if type has no subtype).
	 */

	Type(ValueType rawType, TypeReference subType);
	virtual ~Type();

	/**
	 * Get this types primitive type.
	 */

	ValueType getType() {
		return rawType_;
	}

	bool isPrimitive() {

		switch (rawType_) {
		case String:
		case Array:
		case StructureType:
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
	bool Equals(Type* other);

	TypeReference getSubtypeReference();

	virtual std::string getTypeName() {

		switch (getType()) {
		case Array:
			return std::string("array(") + getSubtype()->getTypeName() + ")";
		case Int:
			return "int";
		case Boolean:
			return "bool";
		case String:
			return "string";
		case Void:
			return "void";
		case StructureType:
		case ValueTypeMax:
		case TypeUnresolved:
			break;
		}

		return "ERROR: Unresolved/Illegal Type";
	}


};

#endif /* TYPE_HPP_ */
