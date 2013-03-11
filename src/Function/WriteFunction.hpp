#ifndef _WRITE_FUNCTION_H_
#define _WRITE_FUNCTION_H_
#include "Function.hpp"

class WriteFunction: public Function {
public:
	Value* execute(std::vector<Value*> arguments);

	ValueType type() {
		return Void;
	}

	unsigned int numArgs() {
		return 1;
	}

	ValueType argType(int arg) {

		if (arg == 0) {
			return String;
		}

		return Void;
	}
};

#endif //_WRITE_FUNCTION_H_
