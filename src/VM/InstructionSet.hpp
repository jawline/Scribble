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
	InstructionSet() : numInstructions_(0), numConstants_(0), start_(0) {}
	InstructionSet(uint8_t* instructions, size_t numInstructions, uint8_t* constants, size_t numConstants, unsigned int start);
	virtual ~InstructionSet();

	/**
	 * Returns the index of the first instruction to execute ( In bytes ).
	 */

	unsigned int getStartLocation();

	/**
	 * Return the size of the instruction set in bytes.
	 */

	unsigned int getSizeInBytes();

	/**
	 * Return the byte from instructions at the given index i.
	 */

	uint8_t getByte(size_t i);

	/**
	 * Return the integer from instructions at the given index i.
	 */

	int getInt(size_t i);

	/**
	 * Return the long ( 8 bytes ) from instructions at given index i.
	 */

	long getLong(size_t i);

	/**
	 * Return a byte from the constant memory for this instruction set at index i.
	 */

	uint8_t getConstantByte(size_t index);

	/**
	 * Return a int from the constant memory for this instruction set at index i.
	 */

	int getConstantInt(size_t index);

	/**
	 * Return a long from the constant memory for this instruction set at index i.
	 */

	long getConstantLong(size_t index);

	/**
	 * Return a 32 bit float from the constant memory for this instruction set at index i.
	 */

	float32_t getConstantFloat32(size_t index);

	/**
	 * Return a string from this constant memory for this instruction set at index i.
	 */

	char* getConstantString(size_t index);

	/**
	 * Return a pointer to the instruction sets memory.
	 */

	uint8_t* getInstructionsPointer();

	/**
	 * Return a pointer to the constant memory for a instruction set.
	 */

	uint8_t* getConstantsPointer();
};

} /* namespace VM */
#endif /* INSTRUCTIONSET_HPP_ */
