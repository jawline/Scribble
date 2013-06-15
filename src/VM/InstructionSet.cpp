/*
 * InstructionSet.cpp
 *
 *  Created on: 10 Jun 2013
 *      Author: blake
 */

#include "InstructionSet.hpp"

namespace VM {

InstructionSet::InstructionSet(uint8_t* instructions, size_t numInstructions,
		uint8_t* constants, size_t numConstants, unsigned int start) :
		instructions_(instructions), numInstructions_(numInstructions), constants_(
				constants), numConstants_(numConstants), start_(start) {
}

InstructionSet::~InstructionSet() {
	// TODO Auto-generated destructor stub
}

uint8_t* InstructionSet::instructions() {
	return instructions_;
}

unsigned int InstructionSet::startInstruction() {
	return start_;
}

unsigned int InstructionSet::numInstructions() {
	return numInstructions_;
}

} /* namespace VM */
