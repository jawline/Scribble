#ifndef _INT_H_
#define _INT_H_
#include "Value.hpp"
#include <Statement/Heap.hpp>

class IntValue : public Value {
private:
	int value_;

public:
	IntValue(int value) {
		value_ = value;
	}

	ValueType type();

	int value();

	void setValue(int v);

	Value* clone();

	void applyOperator(ValueOperator v, Value* r);
};

#endif //_INT_H_
