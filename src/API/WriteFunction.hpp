#ifndef _WRITE_FUNCTION_H_
#define _WRITE_FUNCTION_H_
#include "Function.hpp"

class WriteFunction: public Function {
public:

	WriteFunction(std::string ns) :
			Function("Write", ns) {

	}

	virtual void execute(API::APIValue* values,
			VM::VirtualMachine* virt) {
		printf("%s", (char*) values[0].getReferencePointer());
	}

	Value* execute(std::vector<Value*> arguments);

	Type* getType();
	const unsigned int numArgs();
	Type* argType(unsigned int arg);

	virtual std::string getName() {
		return "NativeWriteString";
	}

};

#endif //_WRITE_FUNCTION_H_
