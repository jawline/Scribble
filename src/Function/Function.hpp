#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <Value/Value.hpp>
#include <vector>

/**
 * Virtual Function class implemented to create Scribble functions.
 * @author Blake Loring
 */
class Function {
public:
	virtual ~Function() {
	}

	virtual Value* execute(std::vector<Value*> arguments) = 0;
	virtual const ValueType getType() = 0;
	virtual const unsigned int numArgs() = 0;
	virtual const ValueType argType(int arg) = 0;
	virtual void check() = 0;
};

#endif //_FUNCTION_H_
