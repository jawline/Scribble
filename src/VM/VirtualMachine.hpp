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

enum VMLogLevel {
	Log,
	Debug,
	Warn,
	Fatal
};

class VMState {
public:
	SmartPointer<VMFunc> func_;
	long pc_;

	VMState() :
	pc_(0) {
	}

	VMState(SmartPointer<VMFunc> func, long pc) :
	func_(func), pc_(pc) {
	}
};

class VirtualMachine {
private:

	/**
	 * Pointer to the actual stack memory
	 */

	uint8_t* stack_;

	/**
	 * Current max stack height
	 */

	long currentStackHeight_;

	/**
	 * A list of the location of each reference on the stack.
	 */

	std::vector<long> stackReferences_;

	/**
	 * The virtual machine state stack is pushed every time a function call is made with the new instruction set and popped on return. The storedPc is used to store the value of the PC register on a function call so on return it can be restored.
	 */

	std::stack<VMState> currentVmState_;

	/**
	 * Pointer to registers and whether they are a reference.
	 */

	long currentInstruction;
	long stackBasePointer;
	long stackCurrentPointer;

	int64_t* registers_;
	bool* registerReference_;

	/**
	 * The VM heap.
	 */

	Heap heap_;

	/**
	 * The parent namespace node.
	 */

	VMNamespace namespace_;

	unsigned int gcStat_;

	bool returnToPreviousFunction(SmartPointer<VMFunc>& fn, InstructionSet& set);

	void opLoadConstant(InstructionSet& instructionSet);

public:
	VirtualMachine();
	virtual ~VirtualMachine();

	virtual long stackLong(int64_t pos);
	virtual void stackSetLong(int64_t pos, int64_t v);
	virtual void popStackLong(int64_t& val, bool& ref);
	virtual void pushStackLong(int64_t v);
	virtual void expandStack();
	virtual void markStackReference();
	virtual void pushRegister(uint8_t reg);

	void getRegister(uint8_t reg, int64_t& val, bool& isReg);
	void setRegister(uint8_t reg, int64_t val, bool ref);

	virtual Heap& getHeap() {
		return heap_;
	}

	virtual SmartPointer<VMEntryType> findType(std::string name);

	virtual void registerEntry(std::string name, NamespaceEntry entry) {
		namespace_.insert(name, entry);
	}

	virtual void execute(std::string function);
	virtual void garbageCollection();

	virtual void printState();
	virtual void hitGc() {
		gcStat_++;
	}

	virtual void logMessage(VMLogLevel, std::string message);
};

} /* namespace VM */

#endif /* VIRTUALMACHINE_HPP_ */
