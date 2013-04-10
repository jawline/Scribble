#ifndef _INT_H_
#define _INT_H_
#include "Value.hpp"

class IntValue : public Value {
private:
	int value_;

public:
	IntValue(int value) {
		value_ = value;
	}

	ValueType type() {
		return Int;
	}

	int value() {
		return value_;
	}

	void setValue(int v) {
		value_ = v;
	}

	Value* clone() {
		return new IntValue(value_);
	}

	void applyOperator(ValueOperator v, Value* r);
};

#endif //_INT_H_
