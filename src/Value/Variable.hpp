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

	void setType(ValueType newType);
	void setValue(Value* v);
	Value* getValue();
	ValueType getType();
	void setPosition(int pos);
	int getPosition();

};

#endif //_VARIABLE_H_
