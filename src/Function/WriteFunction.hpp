#ifndef _WRITE_FUNCTION_H_
#define _WRITE_FUNCTION_H_
#include "Function.hpp"

class WriteFunction: public Function {
public:
	Value* execute(std::vector<Value*> arguments);

	const ValueType getType();
	const unsigned int numArgs();
	const ValueType argType(unsigned int arg);

	virtual void check() {
	}
};

#endif //_WRITE_FUNCTION_H_
