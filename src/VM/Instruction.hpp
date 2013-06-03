/*
 * Instruction.hpp
 *
 *  Created on: 28 May 2013
 *      Author: blake
 */

#ifndef INSTRUCTION_HPP_
#define INSTRUCTION_HPP_
#include "OpCodes.hpp"
#include <Value/Value.hpp>

namespace VM {

struct Instruction {

	Instruction(OpCodes code, Value* data) {
		this->code = code;
		this->data = data;
	}

	OpCodes code;
	Value* data;
};

} /* namespace VM */

#endif /* INSTRUCTION_HPP_ */
