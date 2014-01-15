/*
 * APIValue.cpp
 *
 *  Created on: 10 Sep 2013
 *      Author: blake
 */

#include "APIValue.hpp"

namespace API {

APIValue::APIValue(Type* type, int64_t val) :
		cType_(type), vType_(nullptr), data_(nullptr), val_(val) {
}

APIValue::APIValue(Type* type, SmartPointer<VM::VMEntryType> vmType, SmartPointer<uint8_t> data, long val) :
cType_(type), vType_(vmType), data_(data), val_(val) {

}

APIValue::~APIValue() {

}

} /* namespace API */
