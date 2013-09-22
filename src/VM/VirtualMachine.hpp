/*
 * VirtualMachine.hpp
 *
 *  Created on: 28 May 2013
 *      Author: blake
 */

#ifndef VIRTUALMACHINE_HPP_
#define VIRTUALMACHINE_HPP_
#include "InstructionSet.hpp"
#include "VMFunc.hpp"
#include <vector>
#include <map>
#include <stack>
#include "Stack.hpp"
#include "Heap.hpp"
#include "VMNamespace.hpp"
#include "VMEntryType.hpp"

namespace VM {

class VMState {
public:
	InstructionSet set_;
	long pc_;

	VMState() :
			pc_(0) {
	}

	VMState(InstructionSet set, long pc) : set_(set), pc_(pc) {}
};

class VirtualMachine {
private:
	uint8_t* stack_;
	long currentStackHeight_;
	std::vector<long> stackReferences_;

	/**
	 * The virtual machine state stack is pushed every time a function call is made with the new instruction set and popped on return. The storedPc is used to store the value of the PC register on a function call so on return it can be restored.
	 */

	std::stack<VMState> currentVmState_;

	long* registers_;
	bool* registerReference_;
	Heap heap_;
	VMNamespace namespace_;

	unsigned int gcStat_;

public:
	VirtualMachine();
	virtual ~VirtualMachine();

	virtual long stackLong(long pos);
	virtual void stackSetLong(long pos, long v);
	virtual void popStackLong(long& val, bool& ref);
	virtual void pushStackLong(long v);
	virtual void expandStack();
	virtual void markStackReference();
	virtual void pushRegister(uint8_t reg);

	virtual long getRegister(uint8_t reg) {
		return registers_[reg];
	}

	virtual void setRegister(uint8_t reg, long val, bool ref) {
		registers_[reg] = val;
		registerReference_[reg] = ref;
	}

	virtual Heap& getHeap() {
		return heap_;
	}

	virtual SP<VMEntryType> findType(std::string name);

	virtual void registerEntry(std::string name, NamespaceEntry entry) {
		namespace_[name] = entry;
	}

	virtual void execute(std::string function);
	virtual void garbageCollection();

	virtual void printState();
	virtual void hitGc() {
		gcStat_++;
	}
};

} /* namespace VM */

#endif /* VIRTUALMACHINE_HPP_ */
