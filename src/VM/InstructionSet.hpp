/*
 * InstructionSet.hpp
 *
 *  Created on: 10 Jun 2013
 *      Author: blake
 */

#ifndef INSTRUCTIONSET_HPP_
#define INSTRUCTIONSET_HPP_
#include <stdint.h>
#include <vector>

namespace VM {

class InstructionSet {
private:
	uint8_t* instructions_;
	unsigned int numInstructions_;
	unsigned int start_;

public:
	InstructionSet(uint8_t* instructions, unsigned int numInstructions, unsigned int start);
	virtual ~InstructionSet();

	unsigned int startInstruction();
	unsigned int numInstructions();

	uint8_t getInst(long i) {
		return instructions_[i];
	}

	int getInt(long i) {
		return *(int*)(instructions_ + i);
	}

	long getLong(long i) {
		return *(long*)(instructions_ + i);
	}

	uint8_t* instructions();
};

} /* namespace VM */
#endif /* INSTRUCTIONSET_HPP_ */
