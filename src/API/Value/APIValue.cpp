/*
 * APIValue.cpp
 *
 *  Created on: 10 Sep 2013
 *      Author: blake
 */

#include "APIValue.hpp"

namespace API {

APIValue::APIValue(int64_t val) :
		virt_(nullptr), type_(nullptr), data_(nullptr), val_(val) {
}

APIValue::APIValue(SmartPointer<VM::VMEntryType> type, uint8_t* data, long val, VM::VirtualMachine* virt) :
virt_(virt), type_(type), data_(data), val_(val) {

	//Lock the reference so the VM doesn't free it even if its no longer used in Scribble
	virt_->getHeap().lock(val_);

}

APIValue::~APIValue() {

	//If this is a heap reference then unlock it notifying Scribble that the
	//Gc can delete it again ( As long as no other locks exist )

	if (virt_ != nullptr && data_ != nullptr) {
		virt_->getHeap().unlock(val_);
	}

}

} /* namespace API */
