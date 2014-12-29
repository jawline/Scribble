/*
 * VirtualMachine_Stack.cpp
 *
 *  Created on: 24 Oct 2013
 *      Author: blake
 */

#include "VirtualMachine.hpp"
#include "VirtualMachine_Debug.hpp"

namespace VM {

long VirtualMachine::stackLong(int64_t pos) {
    //VM_PRINTF_LOG("Returning stack value at address %li\n", pos);

    //Return the value of the stack at a given position pos in bytes.

    return *((long*) (stack_ + pos));
}

void VirtualMachine::stackSetLong(int64_t pos, int64_t v) {
    //VM_PRINTF_LOG("Setting stack value at position %li\n", pos);
    //Set the value of the stack at index pos in bytes to the value v.
    *((long*) (stack_ + pos)) = v;
}

void VirtualMachine::popStackLong(int64_t& val, bool& ref) {

    if (stackCurrentPointer < 8) {
        VM_PRINTF_FATAL("Error - Cannot pop on empty stack. Stack current pointer %li\n", stackCurrentPointer);
    }

    val = stackLong(stackCurrentPointer - 8);
    stackCurrentPointer = stackCurrentPointer - 8;

    ref = false;

    if (stackReferences_.size() > 0
            && stackReferences_.back() >= stackCurrentPointer) {
        stackReferences_.pop_back();
        ref = true;
    }

    //VM_PRINTF_LOG("Popped long %li from stack. Current Stack pointer is now %li\n", val, stackCurrentPointer);
}

void VirtualMachine::pushStackLong(int64_t v) {

    //Work out the current maximum address of the stack.
    long max = stackCurrentPointer + 8;

    //If max >= currentStackHeight then expand the stack a bit.
    while (max >= currentStackHeight_) {
        expandStack();
    }

    stackSetLong(stackCurrentPointer, v);
    stackCurrentPointer = stackCurrentPointer + 8;

    //VM_PRINTF_LOG("Pushed long to stack now %li value %li\n", stackCurrentPointer, v);
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

/**
 * Mark the next entry pushed to the stack as a reference
 */

void VirtualMachine::markStackReference() {
    stackReferences_.push_back(stackCurrentPointer);
}

}
