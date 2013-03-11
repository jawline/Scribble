#ifndef _VARIABLE_H_
#define _VARIABLE_H_
#include <Pointers/SmartPointer.hpp>
#include "Value.hpp"
#include <map>

class Variable {
private:
	Value* value_;
	ValueType type_;

public:

	Variable(ValueType t, Value* value);
	~Variable();

	Value* getValue();
	ValueType getType();
};

#endif //_VARIABLE_H_
