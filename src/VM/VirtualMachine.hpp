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
#include <map>
#include "Stack.hpp"
#include "Heap.hpp"

namespace VM {
class VirtualMachine {
private:
	uint8_t* stack_;
	long* registers_;
	bool* registerReference_;
	Heap heap_;
	std::map<std::string, SP<VMEntryType>> registeredTypes_;

	unsigned int gcStat_;

public:
	VirtualMachine();
	virtual ~VirtualMachine();

	virtual long stackLong(long pos);
	virtual void stackSetLong(long pos, long v);
	virtual long popStackLong();
	virtual void pushStackLong(long v);

	virtual void execute(InstructionSet& set);
	virtual void garbageCollection();

	virtual void printState();
};

} /* namespace VM */

#endif /* VIRTUALMACHINE_HPP_ */
