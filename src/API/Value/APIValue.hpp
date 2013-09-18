/*
 * APIValue.hpp
 *
 *  Created on: 10 Sep 2013
 *      Author: blake
 */

#ifndef APIVALUE_HPP_
#define APIVALUE_HPP_
#include <VM/VMEntryType.hpp>

namespace API {

class APIValue {
private:
	SP<VM::VMEntryType> type_;
	uint8_t* data_;
	long val_;

public:
	APIValue() { val_ = 0; type_ = nullptr; data_ = nullptr;}
	APIValue(long val);
	APIValue(SP<VM::VMEntryType> type, uint8_t* data, long val);
	virtual ~APIValue();

	long getValue() {
		return val_;
	}

	SP<VM::VMEntryType> getReferenceType() {
		return type_;
	}

	uint8_t* getReferencePointer() {
		return data_;
	}

	bool isReference() {
		if (type_.Null()) {
			return false;
		}
		return true;
	}
};

} /* namespace API */
#endif /* APIVALUE_HPP_ */
