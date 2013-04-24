#ifndef _VARIABLE_H_
#define _VARIABLE_H_
#include <Pointers/SmartPointer.hpp>
#include "Value.hpp"
#include <map>

class Variable {
private:
	Value* value_;
	int position_;

public:

	Variable(int position, Value* value);
	~Variable();

	void setValue(Value* v);
	Value* getValue();
	Type* getType();
	void setPosition(int pos);
	int getPosition();

};

#endif //_VARIABLE_H_
