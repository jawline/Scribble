/*
 * VMEntryType.hpp
 *
 *  Created on: Jul 21, 2013
 *      Author: blake
 */

#ifndef VMENTRYTYPE_HPP_
#define VMENTRYTYPE_HPP_
#include <Pointers/SmartPointer.hpp>
#include <string>

namespace VM {

enum VMEntryBaseType {
	VMPrimitive, VMArray, VMStructure
};

class VMEntryType {
private:

	std::string name_;
	unsigned int size_;

	bool reference_;

	VMEntryBaseType baseType_;

	//TODO: Potentially make this a pointer or smart pointer to reduce on space used by types.
	SP<VMEntryType> arraySubtype_;

public:
	VMEntryType(std::string name, unsigned int size, bool reference);
	VMEntryType(std::string name, SP<VMEntryType> subtype);

	virtual ~VMEntryType();

	/**
	 * Return the name of this VMEntryType ( Such as array(int) or int ).
	 */

	std::string typeName();

	/**
	 * Returns the size of the element. Will be either 1, 2, 4, or 8
	 */

	unsigned int getElementSize();

	/**
	 * If base type is VMPrimitive and the VMPrimitive is a heap reference then this will return true.
	 */

	bool isReference();

	/**
	 * Return the base type of this VMEntryType ( VMStructure, VMPrimtive, VMArray ).
	 */

	VMEntryBaseType getBaseType() {
		return baseType_;
	}

	/**
	 * If this object is of the base type VMArray then this function will return a VMEntryType with the subtype of the array.
	 */

	SP<VMEntryType> arraySubtype();

	/**
	 * Return a text description of the VMEntryType
	 */

	std::string debugType();
};

} /* namespace VM */

#endif /* VMENTRYTYPE_HPP_ */
