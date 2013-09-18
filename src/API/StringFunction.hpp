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
#include <sstream>

class IntToStringFunction: public Function {
public:
	IntToStringFunction(std::string ns);
	virtual ~IntToStringFunction();

	Value* execute(std::vector<Value*> arguments);

	Type* getType();
	const unsigned int numArgs();
	Type* argType(unsigned int arg);

	virtual API::APIValue execute(API::APIValue* values,
			VM::VirtualMachine* virt) {
		int toConv = values[0].getValue();
		std::stringstream res;
		res << toConv;
		std::string resultString = res.str();
		long heapEntry = virt->getHeap().allocate(virt->findType("string"), resultString.length() + 1, (uint8_t*) resultString.c_str());
		return API::APIValue(virt->findType("string"), virt->getHeap().getAddress(heapEntry), heapEntry);
	}

};

class BoolToStringFunction: public Function {
public:
	BoolToStringFunction(std::string ns);
	virtual ~BoolToStringFunction();

	Value* execute(std::vector<Value*> arguments);

	 Type* getType();
	const unsigned int numArgs();
	Type* argType(unsigned int arg);

};

#endif /* STRINGFUNCTION_HPP_ */
