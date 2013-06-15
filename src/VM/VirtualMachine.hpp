/*
 * VirtualMachine.hpp
 *
 *  Created on: 28 May 2013
 *      Author: blake
 */

#ifndef VIRTUALMACHINE_HPP_
#define VIRTUALMACHINE_HPP_
#include "InstructionSet.hpp"
#include <vector>
#include "Stack.hpp"

namespace VM {

const static unsigned int vmNumRegisters = 16;
const static unsigned int vmOpCodeSize = 6;
const static unsigned int vmProgramCounter = 0;
const static unsigned int vmStackBasePointer = 1;
const static unsigned int vmStackCurrentPointer = 2;
const static unsigned int vmTempRegisterOne = 3;
const static unsigned int vmTempRegisterTwo = 4;
const static unsigned int vmTempRegisterThree = 5;

class VirtualMachine {
private:
	uint8_t* stack_;
	long* registers_;

public:
	VirtualMachine();
	virtual ~VirtualMachine();

	virtual long stackLong(long pos) {
		return *((long*)stack_+pos);
	}

	virtual void stackSetLong(long pos, long v) {
		*((long*)stack_+pos) = v;
	}

	virtual long popStackLong() {
		long top = stackLong(registers_[vmStackCurrentPointer] - 8);
		registers_[vmStackCurrentPointer] -= 8;
		return top;
	}

	virtual void pushStackLong(long v) {
		stackSetLong(registers_[vmStackCurrentPointer], v);
		registers_[vmStackCurrentPointer] += 8;
	}

	virtual void execute(InstructionSet& set);
	virtual void printState();
};

} /* namespace VM */

#endif /* VIRTUALMACHINE_HPP_ */
