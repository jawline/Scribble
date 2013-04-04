#ifndef _WRITE_FUNCTION_H_
#define _WRITE_FUNCTION_H_
#include "Function.hpp"

class WriteFunction: public Function {
public:
	Value* execute(std::vector<Value*> arguments);

	const ValueType getType() {
		return Void;
	}

	const unsigned int numArgs() {
		return 1;
	}

	const ValueType argType(int arg) {

		if (arg == 0) {
			return String;
		}

		return Void;
	}

	virtual void check() {
	}
};

#endif //_WRITE_FUNCTION_H_
