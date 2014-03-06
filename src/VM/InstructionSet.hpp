/*
 * InstructionSet.hpp
 *
 *  Created on: 10 Jun 2013
 *      Author: blake
 */

#ifndef INSTRUCTIONSET_HPP_
#define INSTRUCTIONSET_HPP_
#include <types.h>
#include <iostream>
#include <vector>
#include <Pointers/SmartPointer.hpp>

namespace VM {

class InstructionSet {
private:

	SmartPointer<uint8_t> instructions_;
	size_t numInstructions_;

	SmartPointer<uint8_t> constants_;
	size_t numConstants_;

	unsigned int start_;

public:
	InstructionSet() : numInstructions_(0), numConstants_(0), start_(0)  { }
	InstructionSet(uint8_t* instructions, size_t numInstructions, uint8_t* constants, size_t numConstants, unsigned int start);
	virtual ~InstructionSet();

	unsigned int startInstruction();
	unsigned int numInstructions();

	uint8_t getInst(size_t i) {
		return instructions()[i];
	}

	int getInt(size_t i) {
		return *(int*)(instructions() + i);
	}

	long getLong(size_t i) {
		return *(long*)(instructions() + i);
	}

	inline uint8_t getConstantByte(size_t index) {
		return constants()[index];
	}

	inline int getConstantInt(size_t index) {
		return *(int*)(constants() + index);
	}

	inline long getConstantLong(size_t index) {
		return *(long*)(constants() + index);
	}

	inline float32_t getConstantFloat32(size_t index) {
		return *(float32_t*)(constants() + index);
	}

	inline char* getConstantString(size_t index) {
		return (char*)(constants() + index);
	}

	uint8_t* instructions();
	uint8_t* constants();
};

} /* namespace VM */
#endif /* INSTRUCTIONSET_HPP_ */
