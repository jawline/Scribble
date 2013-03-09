#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <Value/Value.hpp>
#include <vector>

class Function {
public:
	virtual ~Function() {}
	virtual Value* execute(std::vector<Value*> arguments) = 0;
};

#endif //_FUNCTION_H_
