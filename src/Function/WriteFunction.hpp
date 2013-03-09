#ifndef _WRITE_FUNCTION_H_
#define _WRITE_FUNCTION_H_
#include "Function.hpp"

class WriteFunction : public Function {
public:
	Value* execute(std::vector<Value*> arguments);
};

#endif //_WRITE_FUNCTION_H_
