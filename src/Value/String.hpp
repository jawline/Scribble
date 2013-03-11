#ifndef _STRING_H_
#define _STRING_H_
#include "Value.hpp"
#include <string>

class StringValue : public Value {
private:
	std::string value_;

public:

	StringValue(std::string const value) {
		value_ = std::string(value);	
	}

	ValueType type() {
		return String;
	}

	Value* clone() {
		return new StringValue(value_.c_str());
	}

	void applyOperator(ValueOperator v, Value* r);

	std::string getValue() {
		return value_;
	}
};

#endif //_STRING_H_
