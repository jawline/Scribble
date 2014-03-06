/*
 * InstructionSet.cpp
 *
 *  Created on: 10 Jun 2013
 *      Author: blake
 */

#include "InstructionSet.hpp"
#include <string.h>

namespace VM {

InstructionSet::InstructionSet(uint8_t* instructions, size_t numInstructions,
		uint8_t* constants, size_t numConstants, unsigned int start) :
		numInstructions_(numInstructions), numConstants_(numConstants), start_(
				start) {

	//Allocate memory for and copy over the instruction set
	instructions_ = SmartPointer < uint8_t > (new uint8_t[numInstructions_]);
	constants_ = SmartPointer < uint8_t > (new uint8_t[numConstants_]);
	memcpy(instructions_.get(), instructions, numInstructions_);
	memcpy(constants_.get(), constants, numConstants_);
}

InstructionSet::~InstructionSet() {
	//delete[] instructions_;
	//delete[] constants_;
}

uint8_t* InstructionSet::instructions() {
	return instructions_.get();
}

uint8_t* InstructionSet::constants() {
	return constants_.get();
}

unsigned int InstructionSet::startInstruction() {
	return start_;
}

unsigned int InstructionSet::numInstructions() {
	return numInstructions_;
}

} /* namespace VM */
