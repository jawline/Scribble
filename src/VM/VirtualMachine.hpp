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
const static unsigned int vmProgramCounter = 0;

class VirtualMachine {
private:
	VMStack stack_;
	long* registers_;

public:
	VirtualMachine();
	virtual ~VirtualMachine();

	virtual void execute(InstructionSet& set);
	virtual void printState();
};

} /* namespace VM */

#endif /* VIRTUALMACHINE_HPP_ */
