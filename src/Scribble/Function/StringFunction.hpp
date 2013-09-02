/*
 * StringFunction.hpp
 *
 *  Created on: 10 Mar 2013
 *      Author: blake
 */

#ifndef STRINGFUNCTION_HPP_
#define STRINGFUNCTION_HPP_
#include "Function.hpp"
#include <Scribble/Value/TypeManager.hpp>

class IntToStringFunction: public Function {
public:
	IntToStringFunction();
	virtual ~IntToStringFunction();

	Value* execute(std::vector<Value*> arguments);

	Type* getType();
	const unsigned int numArgs();
	Type* argType(unsigned int arg);

	virtual void check() {
	}

	virtual std::string getName() {
		return "NativeIntToString";
	}

	virtual VM::VMFunc generateVMFunction() {
		return VM::VMFunc(getName(), VM::InstructionSet());
	}
};

class BoolToStringFunction: public Function {
public:
	BoolToStringFunction();
	virtual ~BoolToStringFunction();

	Value* execute(std::vector<Value*> arguments);

	 Type* getType();
	const unsigned int numArgs();
	Type* argType(unsigned int arg);

	virtual void check() {
	}

	virtual std::string getName() {
		return "NativeBoolToString";
	}

	virtual VM::VMFunc generateVMFunction() {
		return VM::VMFunc(getName(), VM::InstructionSet());
	}
};

#endif /* STRINGFUNCTION_HPP_ */
