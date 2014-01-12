/*
 * APIValue.cpp
 *
 *  Created on: 10 Sep 2013
 *      Author: blake
 */

#include "APIValue.hpp"

namespace API {

APIValue::APIValue(int64_t val) :
		type_(nullptr), data_(nullptr), val_(val) {
}

APIValue::APIValue(SmartPointer<VM::VMEntryType> type, SmartPointer<uint8_t> data, long val) :
type_(type), data_(data), val_(val) {

}

APIValue::~APIValue() {

}

} /* namespace API */
