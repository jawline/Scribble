/*
 * InstructionSet.hpp
 *
 *  Created on: 10 Jun 2013
 *      Author: blake
 */

#ifndef INSTRUCTIONSET_HPP_
#define INSTRUCTIONSET_HPP_
#include <stdint.h>
#include <iostream>
#include <vector>

namespace VM {

class InstructionSet {
private:

	uint8_t* instructions_;
	size_t numInstructions_;

	uint8_t* constants_;
	size_t numConstants_;

	unsigned int start_;

public:
	InstructionSet(uint8_t* instructions, size_t numInstructions, uint8_t* constants, size_t numConstants, unsigned int start);
	virtual ~InstructionSet();

	unsigned int startInstruction();
	unsigned int numInstructions();

	uint8_t getInst(size_t i) {
		return instructions_[i];
	}

	int getInt(size_t i) {
		return *(int*)(instructions_ + i);
	}

	long getLong(size_t i) {
		return *(long*)(instructions_ + i);
	}

	uint8_t getConstantByte(size_t index) {
		return constants_[index];
	}

	int getConstantInt(size_t index) {
		return *(int*)(constants_ + index);
	}

	long getConstantLong(size_t index) {
		return *(long*)(constants_ + index);
	}

	uint8_t* instructions();
	uint8_t* constants();
};

} /* namespace VM */
#endif /* INSTRUCTIONSET_HPP_ */
