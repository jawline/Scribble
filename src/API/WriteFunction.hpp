#ifndef _WRITE_FUNCTION_H_
#define _WRITE_FUNCTION_H_
#include "Function.hpp"



/**
 * WriteFunction writes a given string to the command line.
 */

class WriteFunction: public Function {
public:

	WriteFunction(std::string ns);

	virtual API::APIValue execute(API::APIValue* values,
			VM::VirtualMachine* virt);

	ScribbleCore::Type* getType();
	const unsigned int numArgs();
	ScribbleCore::Type* argType(unsigned int arg);

	virtual std::string getName() {
		return "NativeWriteString";
	}

};

#endif //_WRITE_FUNCTION_H_
