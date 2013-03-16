/*
 * StringFunction.hpp
 *
 *  Created on: 10 Mar 2013
 *      Author: blake
 */

#ifndef STRINGFUNCTION_HPP_
#define STRINGFUNCTION_HPP_
#include "Function.hpp"

class StringFunction: public Function {
public:
	StringFunction();
	virtual ~StringFunction();

	Value* execute(std::vector<Value*> arguments);

	ValueType getType() {
		return String;
	}

	unsigned int numArgs() {
		return 1;
	}

	ValueType argType(int arg) {

		if (arg == 0) {
			return Int;
		}

		return Void;
	}

	virtual void check() {

	}
};

#endif /* STRINGFUNCTION_HPP_ */
