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

APIValue::APIValue(SmartPointer<VM::VMEntryType> type, uint8_t* data, long val) :
		type_(type), data_(data), val_(val) {
	// TODO Auto-generated constructor stub

}

APIValue::~APIValue() {
	// TODO Auto-generated destructor stub
}

} /* namespace API */
