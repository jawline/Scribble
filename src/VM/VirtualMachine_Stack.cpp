/*
 * VirtualMachine_Stack.cpp
 *
 *  Created on: 24 Oct 2013
 *      Author: blake
 */

#include "VirtualMachine.hpp"
#include "VirtualMachine_Debug.hpp"

namespace VM {

long VirtualMachine::stackLong(long pos) {
	return *((long*) (stack_ + pos));
}

void VirtualMachine::stackSetLong(long pos, long v) {
	*((long*) (stack_ + pos)) = v;
}

void VirtualMachine::popStackLong(long& val, bool& ref) {
	val = stackLong(registers_[vmStackCurrentPointer] - 8);
	registers_[vmStackCurrentPointer] -= 8;

	ref = false;

	if (stackReferences_.size() > 0
			&& stackReferences_.back() >= registers_[vmStackCurrentPointer]) {
		stackReferences_.pop_back();
		ref = true;
	}

}

void VirtualMachine::expandStack() {

	VM_PRINTF_LOG("Increased stack size by %i blocks to %likb", vmStackIncrement,
			(currentStackHeight_ / 1024));

	//Allocate memory for a larger stack
	uint8_t* newStack = new uint8_t[currentStackHeight_ + vmStackIncrease];

	//Copy over and then free up the existing stack
	memcpy(newStack, stack_, currentStackHeight_);
	delete[] stack_;

	//Change the stack to the new stack
	stack_ = newStack;
	currentStackHeight_ += vmStackIncrease;

}

void VirtualMachine::pushStackLong(long v) {

	long max = registers_[vmStackCurrentPointer] + 32;

	while (max >= currentStackHeight_) {
		expandStack();
	}

	stackSetLong(registers_[vmStackCurrentPointer], v);
	registers_[vmStackCurrentPointer] += 8;
}

/**
 * Mark the next entry pushed to the stack as a reference
 */

void VirtualMachine::markStackReference() {
	stackReferences_.push_back(registers_[vmStackCurrentPointer]);
}

}
