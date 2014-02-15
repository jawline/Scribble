/*
 * ReadLine.hpp
 *
 *  Created on: 5 Jun 2013
 *      Author: blake
 */

#ifndef READLINE_HPP_
#define READLINE_HPP_
#include "Function.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <iostream>
#include <string>

class ReadLine : public Function {
public:
	ReadLine(std::string ns);
	virtual ~ReadLine();

	virtual APIValue execute(API::APIValue* values, VM::VirtualMachine* virt);

	/**
	 * Get the return type of the function.
	 */
	virtual ScribbleCore::Type* getType() {
		return ScribbleCore::getStringType();
	}

	virtual const unsigned int numArgs() {
		return 0;
	}

	virtual ScribbleCore::Type* argType(unsigned int arg) {
		return nullptr;
	}

};

#endif /* READLINE_HPP_ */
