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
    return *((long*) (stack_ + pos));
}

void VirtualMachine::stackSetLong(int64_t pos, int64_t v) {
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

void VirtualMachine::markStackReference() {
    stackReferences_.push_back(stackCurrentPointer);
}

}
