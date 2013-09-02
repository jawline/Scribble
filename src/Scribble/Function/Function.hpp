#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Value/Value.hpp>
#include <vector>
#include <VM/VMFunc.hpp>

/**
 * Virtual Function class implemented to create Scribble functions.
 * @author Blake Loring
 */
class Function {
public:
	virtual ~Function() {
	}

	/**
	 * Execute the function and return the result value.
	 */
	virtual Value* execute(std::vector<Value*> arguments) = 0;

	/**
	 * Get the return type of the function.
	 */
	virtual Type* getType() = 0;
	virtual const unsigned int numArgs() = 0;
	virtual Type* argType(unsigned int arg) = 0;
	virtual void check() = 0;

	virtual int debugCode(std::stringstream& gen) {
		return 0;
	}

	virtual std::string getName() = 0;
	virtual VM::VMFunc generateVMFunction() = 0;
};

typedef SmartPointer<Function> SafeFunction;

#endif //_FUNCTION_H_
