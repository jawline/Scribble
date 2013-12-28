/*
 * APIValue.hpp
 *
 *  Created on: 10 Sep 2013
 *      Author: blake
 */

#ifndef APIVALUE_HPP_
#define APIVALUE_HPP_

/**
 * Defines int32_t, int64_t and float32_t
 */
#include <types.h>

#include <VM/VMEntryType.hpp>
#include <VM/Constants.hpp>

#include <VM/VirtualMachine.hpp>

namespace API {

class APIValue {
private:
	SmartPointer<VM::VMEntryType> type_;
	uint8_t* data_;
	int64_t val_;

public:
	APIValue() {val_ = 0; type_ = nullptr; data_ = nullptr;}
	APIValue(int64_t val);
	APIValue(SmartPointer<VM::VMEntryType> type, uint8_t* data, long val);
	virtual ~APIValue();

	/**
	 * This returns the value as a 64 bit signed integer.
	 */

	int64_t getValue64() {
		return val_;
	}

	/**
	 * This returns the value as a 32 bit signed integer.
	 */

	int32_t getValue32() {
		return val_;
	}

	/**
	 * This returns the value as a 32 bit floating point number.
	 */

	float32_t getValueFloat32() {
		return *((float32_t*) &val_);
	}

	/**
	 * If the value is a string, return a pointer to the string.
	 */

	char* getValueString() {
		return (char*) getReferencePointer();
	}

	/**
	 * Returns true if the value is equal to VM::vmTrue ( The VMs representation of a true boolean ) otherwise returns false.
	 */

	bool getValueBoolean() {

		if (val_ == VM::vmTrue) {
			return true;
		}

		return false;
	}

	/**
	 * If the value is a reference then return its type.
	 */

	SmartPointer<VM::VMEntryType> getReferenceType() {
		return type_;
	}

	/**
	 * For a reference this will return a pointer to the reference data, for primitive types this will return a null pointer.
	 */

	uint8_t* getReferencePointer() {
		return data_;
	}

	/**
	 * Returns true if this APIValue is a reference to a piece of data on the heap.
	 */

	bool isReference() {

		if (type_.get() == nullptr) {
			return false;
		}

		return true;
	}

	static API::APIValue makeString(std::string const& text, VM::VirtualMachine* vm) {

		//Create the new heap entry
		long heapEntry = vm->getHeap().allocate(vm->findType("string"),
				text.length() + 1, (uint8_t*) text.c_str());

		//Make a new API value from it
		return API::APIValue(vm->findType("string"),
				vm->getHeap().getAddress(heapEntry), heapEntry);
	}
};

} /* namespace API */
#endif /* APIVALUE_HPP_ */
