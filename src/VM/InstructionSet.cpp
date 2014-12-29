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

uint8_t* InstructionSet::getInstructionsPointer() {
    return instructions_.get();
}

uint8_t* InstructionSet::getConstantsPointer() {
    return constants_.get();
}

unsigned int InstructionSet::getStartLocation() {
    return start_;
}

unsigned int InstructionSet::getSizeInBytes() {
    return numInstructions_;
}


uint8_t InstructionSet::getByte(size_t i) {
    return getInstructionsPointer()[i];
}

int InstructionSet::getInt(size_t i) {
    return *(int*)(getInstructionsPointer() + i);
}

long InstructionSet::getLong(size_t i) {
    return *(long*)(getInstructionsPointer() + i);
}

uint8_t InstructionSet::getConstantByte(size_t index) {
    return getConstantsPointer()[index];
}

int InstructionSet::getConstantInt(size_t index) {
    return *(int*)(getConstantsPointer() + index);
}

long InstructionSet::getConstantLong(size_t index) {
    return *(long*)(getConstantsPointer() + index);
}

float32_t InstructionSet::getConstantFloat32(size_t index) {
    return *(float32_t*)(getConstantsPointer() + index);
}

char* InstructionSet::getConstantString(size_t index) {
    return (char*)(getConstantsPointer() + index);
}

} /* namespace VM */
