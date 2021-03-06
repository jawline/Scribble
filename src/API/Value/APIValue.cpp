/*
 * APIValue.cpp
 *
 *  Created on: 10 Sep 2013
 *      Author: blake
 */

#include "APIValue.hpp"

namespace API {

APIValue::APIValue(ScribbleCore::Type* type, int64_t val) :
		cType_(type), vType_(nullptr), data_(nullptr), val_(val) {
}

APIValue::APIValue(ScribbleCore::Type* type, SmartPointer<VM::VMEntryType> vmType, SmartPointer<uint8_t> data, int64_t val) :
cType_(type), vType_(vmType), data_(data), val_(val) {

}

APIValue::~APIValue() {

}

APIValue APIValue::getIndex(unsigned int index, VM::VirtualMachine* vm) {

	if (cType_->getType() != ScribbleCore::Array) {
		return API::APIValue();
	}

	if (index > getArrayLength(vm)) {
		return API::APIValue();
	}

	int offset = getReferenceType()->arraySubtype()->getElementSize() * index;

	unsigned char* elementData = data_.get() + offset;
	//TODO: Find somewhere to consolidate all the various switch statements (4 in the VM, 2 outside of it, if I ever change the byte sizes of primitives it could be an issue)

	int64_t res = 0;

	switch (getReferenceType()->arraySubtype()->getElementSize()) {
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

	if (getReferenceType()->arraySubtype()->isReference()) {
		return API::APIValue(cType_->getSubtype(),
				getReferenceType()->arraySubtype(),
				vm->getHeap().getSmartPointer(res), res);
	} else {
		return API::APIValue(cType_->getSubtype(), res);
	}

}

void APIValue::setField(std::string const& name, API::APIValue val,
		VM::VirtualMachine* vm) {

	if (cType_->getType() != ScribbleCore::StructureType) {
		return;
	}

	ScribbleCore::StructureInfo* info = (ScribbleCore::StructureInfo*) cType_;

	int index = info->getFieldIndex(name);

	if (index == -1) {
		return;
	}

	int offset = getReferenceType()->getStructureFieldOffset(index);

	unsigned char* elementData = data_.get() + offset;
	//TODO: Find somewhere to consolidate all the various switch statements (4 in the VM, 2 outside of it, if I ever change the byte sizes of primitives it could be an issue)

	switch (getReferenceType()->getStructureFields()[index]->getType()->getElementSize()) {
	case 1:
		(*(int8_t*) elementData) = val.getValue64();
		break;
	case 2:
		(*(int16_t*) elementData) = val.getValue64();
		break;
	case 4:
		(*(int32_t*) elementData) = val.getValue64();
		break;
	case 8:
		(*(int64_t*) elementData) = val.getValue64();
		break;
	default:
		printf("Issues");
		return;
		break;
	}

}

void APIValue::setIndex(unsigned int index, API::APIValue val,
		VM::VirtualMachine* vm) {

	if (cType_->getType() != ScribbleCore::Array) {
		return;
	}

	if (index > getArrayLength(vm)) {
		return;
	}

	//TODO: Check against array length

	int offset = getReferenceType()->arraySubtype()->getElementSize() * index;

	unsigned char* elementData = data_.get() + offset;
	//TODO: Find somewhere to consolidate all the various switch statements (4 in the VM, 2 outside of it, if I ever change the byte sizes of primitives it could be an issue)

	switch (getReferenceType()->arraySubtype()->getElementSize()) {
	case 1:
		(*(int8_t*) elementData) = val.getValue64();
		break;
	case 2:
		(*(int16_t*) elementData) = val.getValue64();
		break;
	case 4:
		(*(int32_t*) elementData) = val.getValue64();
		break;
	case 8:
		(*(int64_t*) elementData) = val.getValue64();
		break;
	default:
		printf("Issues");
		return;
		break;
	}

}

void APIValue::pushToVM(VM::VirtualMachine* virt) {

	if (isReference()) {
		virt->markStackReference();
	}

	virt->pushStackLong(val_);
}

API::APIValue APIValue::makeString(std::string const& text,
		VM::VirtualMachine* vm) {

	//Create the new heap entry
	long heapEntry = vm->getHeap().allocate(
			vm->findType(ScribbleCore::getStringType()->getTypeName()),
			text.length() + 1, (uint8_t*) text.c_str());

	//Make a new API value from it
	return API::APIValue(ScribbleCore::getStringType(),
			vm->findType(ScribbleCore::getStringType()->getTypeName()),
			vm->getHeap().getSmartPointer(heapEntry), heapEntry);
}

API::APIValue APIValue::makeInt32(int val) {
	return API::APIValue(ScribbleCore::getIntType(), val);
}

API::APIValue APIValue::makeFloat32(float32_t val) {
	return API::APIValue(ScribbleCore::getFloat32Type(), *((long*) &val));
}

API::APIValue APIValue::makeBoolean(bool state) {
	return API::APIValue(ScribbleCore::getBooleanType(),
			state ? VM::vmTrue : VM::vmFalse);
}

SmartPointer<VM::VMEntryType> APIValue::getReferenceType() const {
	return vType_;
}

uint8_t* APIValue::getReferencePointer() const {
	return data_.get();
}

ScribbleCore::Type* APIValue::getType() const {
	return cType_;
}

bool APIValue::isReference() const {

	if (vType_.get() == nullptr) {
		return false;
	}

	return true;
}

bool APIValue::isNull() const {

	if (val_ == 0) {
		return true;
	}

	return false;
}

APIValue APIValue::getField(std::string const& name,
		VM::VirtualMachine* vm) const {

	if (cType_->getType() != ScribbleCore::StructureType) {
		return APIValue();
	}

	ScribbleCore::StructureInfo* info = (ScribbleCore::StructureInfo*) cType_;

	int index = info->getFieldIndex(name);

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
		return API::APIValue(info->getFieldType(name),
				getReferenceType()->getStructureFields()[index]->getType(),
				vm->getHeap().getSmartPointer(res), res);
	} else {
		return API::APIValue(info->getFieldType(name), res);
	}

}

unsigned int APIValue::getArrayLength(VM::VirtualMachine* vm) const {

	if (cType_->getType() != ScribbleCore::Array) {
		return 0;
	}

	if (isNull()) {
		return 0;
	}

	return vm->getHeap().getSize(val_)
			/ getReferenceType()->arraySubtype()->getElementSize();
}

} /* namespace API */
