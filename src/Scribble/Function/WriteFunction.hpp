#ifndef _WRITE_FUNCTION_H_
#define _WRITE_FUNCTION_H_
#include "Function.hpp"

class WriteFunction: public Function {
public:
	Value* execute(std::vector<Value*> arguments);

	Type* getType();
	const unsigned int numArgs();
	Type* argType(unsigned int arg);

	virtual void check() {
	}

	virtual std::string getName() {
		return "NativeWriteString";
	}

	virtual VM::VMFunc generateVMFunction() {
		return VM::VMFunc(getName(), VM::InstructionSet());
	}
};

#endif //_WRITE_FUNCTION_H_
