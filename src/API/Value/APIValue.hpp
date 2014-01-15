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
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Value/Type.hpp>
#include <Scribble/Value/StructureInfo.hpp>
#include <Scribble/Value/TypeManager.hpp>

namespace API {

static std::string cStringTypename = "string";

class APIValue {
private:
	SmartPointer<VM::VMEntryType> vType_;
	SmartPointer<uint8_t> data_;
	int64_t val_;
	Type* cType_;

public:
	APIValue() {cType_ = getVoidType(); val_ = 0; vType_ = nullptr; data_ = nullptr;}
	APIValue(Type* type, int64_t val);
	APIValue(Type* type, SmartPointer<VM::VMEntryType> vmType, SmartPointer<uint8_t> data, long val);
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
		return vType_;
	}

	/**
	 * For a reference this will return a pointer to the reference data, for primitive types this will return a null pointer.
	 */

	uint8_t* getReferencePointer() {
		return data_.get();
	}

	Type* getType() {
		return cType_;
	}

	/**
	 * Returns true if this APIValue is a reference to a piece of data on the heap.
	 */

	bool isReference() {

		if (vType_.get() == nullptr) {
			return false;
		}

		return true;
	}

	bool isNull() {

		if (val_ == 0) {
			return true;
		}

		return false;
	}

	APIValue getField(std::string const& name, VM::VirtualMachine* vm) {

		if (cType_->getType() != StructureType) {
			return APIValue();
		}

		StructureInfo* info = (StructureInfo*) cType_;

		int index = info->getIndex(name);

		if (index == -1) {
			return APIValue();
		}

		int offset = getReferenceType()->getStructureFieldOffset(index);

		long res = 0;

		unsigned char* elementData = data_.get() + offset;
		//TODO: Find somewhere to consolidate all the various switch statements (4 in the VM, 2 outside of it, if I ever change the byte sizes of primitives it could be an issue)

		switch (getReferenceType()->getStructureFields()[index]->getType()->getElementSize()) {
			case 1:
			res = (int64_t) (*elementData);
			break;
			case 2:
			res = (int64_t) (*((int16_t*) elementData));
			break;
			case 4:
			res = (int64_t) (*((int32_t*) elementData));
			break;
			case 8:
			res = (int64_t) (*((int64_t*) elementData));
			break;
			default:
			printf("Issues");
			return API::APIValue();
			break;
		}

		if (getReferenceType()->getStructureFields()[index]->getType()->isReference()) {
			return API::APIValue(info->getType(name), getReferenceType()->getStructureFields()[index]->getType(), vm->getHeap().getSmartPointer(res), res);
		} else {
			return API::APIValue(info->getType(name), res);
		}

	}

	void pushToVM(VM::VirtualMachine* virt) {

		if (isReference()) {
			virt->markStackReference();
		}

		virt->pushStackLong(val_);
	}

	static API::APIValue makeFloat32(float32_t val) {
		return API::APIValue(getFloat32Type(), *((long*)&val) );
	}

	static API::APIValue makeString(std::string const& text, VM::VirtualMachine* vm) {

		//Create the new heap entry
		long heapEntry = vm->getHeap().allocate(vm->findType(cStringTypename),
				text.length() + 1, (uint8_t*) text.c_str());

		//Make a new API value from it
		return API::APIValue(getStringType(), vm->findType(cStringTypename),
				vm->getHeap().getSmartPointer(heapEntry), heapEntry);
	}
};

} /* namespace API */
#endif /* APIVALUE_HPP_ */
