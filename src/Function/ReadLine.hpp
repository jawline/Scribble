/*
 * ReadLine.hpp
 *
 *  Created on: 5 Jun 2013
 *      Author: blake
 */

#ifndef READLINE_HPP_
#define READLINE_HPP_
#include "Function.hpp"
#include <Value/TypeManager.hpp>
#include <Value/String.hpp>
#include <Statement/Heap.hpp>
#include <iostream>
#include <string>

class ReadLine : public Function {
public:
	ReadLine();
	virtual ~ReadLine();

	/**
	 * Execute the function and return the result value.
	 */
	virtual Value* execute(std::vector<Value*> arguments) {
		std::string line;
		std::getline(std::cin, line);

		StringValue* newValue = (StringValue*) valueHeap.make(getStringType());
		newValue->setValue(line);
		return newValue;
	}

	/**
	 * Get the return type of the function.
	 */
	virtual Type* getType() {
		return getStringType();
	}

	virtual const unsigned int numArgs() {
		return 0;
	}

	virtual Type* argType(unsigned int arg) {
		return nullptr;
	}

	virtual void check() {

	}
};

#endif /* READLINE_HPP_ */
