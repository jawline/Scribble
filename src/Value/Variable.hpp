#ifndef _VARIABLE_H_
#define _VARIABLE_H_
#include <Pointers/SmartPointer.hpp>
#include "Value.hpp"
#include <map>

class Variable {
private:
	Value* value_;
	int position_;
	ValueType type_;

public:

	Variable(ValueType t, int position, Value* value);
	~Variable();

	Value* getValue();
	ValueType getType();

	void setPosition(int pos) {
		position_ = pos;
	}

	int getPosition() {
		return position_;
	}

};

#endif //_VARIABLE_H_
