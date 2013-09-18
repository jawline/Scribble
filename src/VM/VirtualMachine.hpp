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
#include "Stack.hpp"
#include "Heap.hpp"
#include "VMNamespace.hpp"
#include "VMEntryType.hpp"

namespace VM {
class VirtualMachine {
private:
	uint8_t* stack_;
	std::vector<long> stackReferences_;

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
