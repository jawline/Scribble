/*
 * VirtualMachine.hpp
 *
 *  Created on: 28 May 2013
 *      Author: blake
 */

#ifndef VIRTUALMACHINE_HPP_
#define VIRTUALMACHINE_HPP_
#include "Instruction.hpp"
#include <vector>
#include <Stack/Stack.hpp>

namespace VM {

class VirtualMachine {
private:
	Stack<Value*> stack_;

public:
	VirtualMachine();
	virtual ~VirtualMachine();

	virtual void execute(unsigned int start, std::vector<Instruction> instructions);
};

} /* namespace VM */

#endif /* VIRTUALMACHINE_HPP_ */
