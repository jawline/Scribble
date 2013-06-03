#ifndef _VARIABLE_H_
#define _VARIABLE_H_
#include <Parser/TypeReference.hpp>
#include <Pointers/SmartPointer.hpp>
#include "Value.hpp"
#include <map>

/**
 *
 */

class Variable {
private:
	Value* value_;
	TypeReference type_;
	int position_;

public:

	Variable(int position, TypeReference type, Value* value);
	~Variable();

	void setValue(Value* v);
	Value* getValue();

	Type* getType();
	void setType(Type* type);

	void setPosition(int pos);
	int getPosition();

};

#endif //_VARIABLE_H_
