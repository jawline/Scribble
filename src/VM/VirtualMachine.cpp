/*
 * VirtualMachine.cpp
 *
 *  Created on: 28 May 2013
 *      Author: blake
 */

#include "VirtualMachine.hpp"
#include "OpCodes.hpp"
#include "JumpTypes.hpp"
#include "Constants.hpp"
#include <API/Function.hpp>
#include <stdio.h>

#define VM_DEBUG 3

#define VM_PRINTF_FATAL(fmt, ...) printf(fmt, __VA_ARGS__); do { } while (1)

#if VM_DEBUG == 3
#define VM_PRINTF_DBG(fmt, ...) printf(fmt, __VA_ARGS__)
#define VM_PRINTF_WARN(fmt, ...) printf(fmt, __VA_ARGS__)
#define VM_PRINTF_LOG(fmt, ...) printf(fmt, __VA_ARGS__)
#elif VM_DEBUG == 2
#define VM_PRINTF_DBG(fmt, ...) printf(fmt, __VA_ARGS__)
#define VM_PRINTF_WARN(fmt, ...) printf(fmt, __VA_ARGS__)
#define VM_PRINTF_LOG(fmt, ...)
#elif VM_DEBUG == 1
#define VM_PRINTF_DBG(fmt, ...)
#define VM_PRINTF_WARN(fmt, ...) printf(fmt, __VA_ARGS__)
#define VM_PRINTF_LOG(fmt, ...)
#else
#define VM_PRINTF_WARN(fmt, ...)
#define VM_PRINTF_DBG(fmt, ...)
#define VM_PRINTF_LOG(fmt, ...)
#endif

namespace VM {

VirtualMachine::VirtualMachine() {
	registers_ = new long[vmNumRegisters];
	registerReference_ = new bool[vmNumRegisters];

	for (unsigned int i = 0; i < vmNumRegisters; ++i) {
		registers_[i] = 0;
		registerReference_[i] = false;
	}

	registerEntry("char", NamespaceEntry(new VMEntryType("char", 1, false)));
	registerEntry("int", NamespaceEntry(new VMEntryType("int", 4, false)));
	registerEntry("long", NamespaceEntry(new VMEntryType("int", 8, false)));

	registerEntry("string",
			NamespaceEntry(
					new VMEntryType("string",
							namespace_["char"].getTypeReference())));

	stack_ = new uint8_t[4086];
}

VirtualMachine::~VirtualMachine() {
	// TODO Auto-generated destructor stub
}

SP<VMEntryType> VirtualMachine::findType(std::string name) {

	NamespaceEntry entry;

	if (!searchNamespace(namespace_, name, entry)) {

		char const* prefix = "array(";

		if (strncmp(prefix, name.c_str(), strlen(prefix)) == 0) {

			std::string subtypeName = name.substr(strlen(prefix),
					name.size() - strlen(prefix) - 1);
			SP<VMEntryType> subtype = findType(subtypeName);

			if (subtype.Null()) {
				printf("Cannot create array of invalid subtype %s\n",
						subtypeName.c_str());
				return nullptr;
			}

			SP<VMEntryType> entryType = new VMEntryType(name, subtype);
			registerEntry(name, entryType);
			VM_PRINTF_LOG("Generating new type %s\n", name.c_str());
			return entryType;
		}

		return nullptr;
	}

	if (entry.getType() != Type) {
		return nullptr;
	}

	return entry.getTypeReference();
}

void VirtualMachine::execute(std::string function) {

	NamespaceEntry functionEntry;

	if (!VM::searchNamespace(namespace_, function, functionEntry)
			|| functionEntry.getType() != Function) {
		VM_PRINTF_FATAL("%s is not a registered function\n", function.c_str());
	}

	if (functionEntry.getFunction().isNative()) {
		functionEntry.getFunction().getFunction()->execute(this);
		return;
	} else {
		printf("NOT A NATIVE CALL\n");
	}

	InstructionSet set = functionEntry.getFunction().getInstructions();

	registers_[vmProgramCounter] = set.startInstruction();
	long* current = &registers_[vmProgramCounter];
	bool shouldReturn = false;

	while (!shouldReturn && *current < set.numInstructions()) {

		switch (set.getInst(*current)) {

		case OpLoadConstant: {

			int constantDataStart = set.getInt(*current + 1);
			uint8_t destinationRegister = set.getInst(*current + 5);

			switch (set.getConstantByte(constantDataStart)) {

			case CInt:
				registers_[destinationRegister] = set.getConstantInt(
						constantDataStart + 1);
				registerReference_[destinationRegister] = false;
				break;

			case CLong:
				registers_[destinationRegister] = set.getConstantLong(
						constantDataStart + 1);
				registerReference_[destinationRegister] = false;
				break;

			case CArray: {

				//Read in the type of array from the constant data with this instruction set.
				std::string type = set.getConstantString(constantDataStart + 1);

				//Check the type is valid
				if (namespace_[type].getType() != Type) {
					VM_PRINTF_FATAL("Invalid type %s\n", type.c_str());
				}

				//Essentially a pointer to the next constant bit to read
				int next = constantDataStart + 2 + type.size();

				//Get the size of the area to create
				int sizeBytes = set.getConstantInt(next);
				next += 4;

				//Get the size stored. Will be filled from the start. Any remaining space will be zero'd
				int sizeStored = set.getConstantInt(next);
				next += 4;

				uint8_t* initial = new uint8_t[sizeBytes];

				//Cheap optimization. As you know that this data is about to be written don't wipe the array from the start but instead wipe it from the end of the area
				memset(initial + sizeStored, 0, sizeBytes - sizeStored);

				for (int i = 0; i < sizeStored; ++i) {
					initial[i] = set.getConstantByte(next);
					next++;
				}

				registers_[destinationRegister] = heap_.allocate(
						namespace_[type].getTypeReference(), sizeBytes,
						initial);

				delete[] initial;

				registerReference_[destinationRegister] = true;
				gcStat_++;

				break;
			}

			default:
				printf("Unhandled load %i\n",
						set.getConstantByte(constantDataStart));
				break;

			}

			*current += vmOpCodeSize;
			break;
		}

		case OpMove: {
			uint8_t target = set.getInst(*current + 1);
			uint8_t dest = set.getInst(*current + 2);
			registers_[dest] = registers_[target];
			registerReference_[dest] = registerReference_[target];
			VM_PRINTF_LOG("VM Move %i to %i %i to %i\n",
					target, dest, registerReference_[dest], registerReference_[target]);
			*current += vmOpCodeSize;
			break;
		}

		case OpJump: {

			uint8_t mode = set.getInst(*current + 1);
			int dest = set.getInt(*current + 2);

			switch (mode) {

			case DirectRelative: {
				long dOld = *current;
				long dRest = ((long) dest) * ((long) vmOpCodeSize);
				dOld = dOld + dRest;
				*current = dOld;
				VM_PRINTF_LOG("Jump direct relative to %li\n", ((long) dest));
				break;
			}

			case DirectExact:
				*current = (((long) dest) * ((long) vmOpCodeSize));
				break;

			case RegisterRelative:
				*current += (registers_[dest] * ((long) vmOpCodeSize));
				break;

			case RegisterExact:
				*current = (registers_[dest] * ((long) vmOpCodeSize));
				break;

			}

			break;
		}

		case OpAdd: {

			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);
			uint8_t dest = set.getInst(*current + 3);

			VM_PRINTF_LOG("Added registers %i and %i. Placing result in %i\n",
					left, right, dest);

			registers_[dest] = registers_[left] + registers_[right];
			registerReference_[dest] = false;

			*current += vmOpCodeSize;
			break;
		}

		case OpSub: {

			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);
			uint8_t dest = set.getInst(*current + 3);

			VM_PRINTF_LOG(
					"Subtracted registers %i and %i. Placing result in %i\n",
					left, right, dest);

			registers_[dest] = registers_[left] - registers_[right];
			registerReference_[dest] = false;

			*current += vmOpCodeSize;
			break;
		}

		case OpMul: {

			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);
			uint8_t dest = set.getInst(*current + 3);

			VM_PRINTF_LOG(
					"Multiplied registers %i and %i. Placing result in %i\n",
					left, right, dest);

			registers_[dest] = registers_[left] * registers_[right];
			registerReference_[dest] = false;

			*current += vmOpCodeSize;
			break;
		}

		case OpDiv: {

			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);
			uint8_t dest = set.getInst(*current + 3);

			VM_PRINTF_LOG("Divided registers %i and %i. Placing result in %i\n",
					left, right, dest);

			registers_[dest] = registers_[left] / registers_[right];
			registerReference_[dest] = false;

			*current += vmOpCodeSize;
			break;
		}

		case OpEqual: {

			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);

			if (registers_[left] == registers_[right]) {
				*current += vmOpCodeSize;
			} else {
				*current += 2 * vmOpCodeSize;
			}

			break;
		}

		case OpLessThan: {
			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);

			if (registers_[left] < registers_[right]) {
				*current += vmOpCodeSize;
			} else {
				*current += 2 * vmOpCodeSize;
			}

			break;
		}

			/**
			 * OpPushRegisters
			 * Push registers, starting from the start register and pushing numregisters sequentially from it
			 * StartRegister - Offset 1 - 1 byte
			 * NumRegisters - Offset 2 - 1 byte
			 */
		case OpPushRegisters: {
			uint8_t startRegister = set.getInst(*current + 1);
			uint8_t numRegisters = set.getInst(*current + 2);

			//printf("Pushing from %i registers from %i\n", numRegisters, startRegister);

			for (uint8_t i = startRegister; i < startRegister + numRegisters;
					i++) {
				pushRegister(i);
			}

			*current += vmOpCodeSize;
			break;
		}

			/**
			 * Pop n registers starting from the start+nth register and the last pop acting on the start register
			 */
		case OpPopRegisters: {
			uint8_t startRegister = set.getInst(*current + 1);
			uint8_t numRegisters = set.getInst(*current + 2);

			//printf("Popping from %i registers from %i\n", ((int)numRegisters), ((int)startRegister));

			for (uint8_t i = (startRegister + numRegisters) - 1;
					i >= startRegister; i--) {
				popStackLong(registers_[i], registerReference_[i]);
			}

			*current += vmOpCodeSize;
			break;
		}

		case OpPopNil: {

			long t;
			bool r;

			popStackLong(t, r);

			*current += vmOpCodeSize;
			break;
		}

		case OpLessThanOrEqual: {
			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);

			if (registers_[left] <= registers_[right]) {
				*current += vmOpCodeSize;
			} else {
				*current += 2 * vmOpCodeSize;
			}

			break;
		}

		case OpArraySet: {

			uint8_t data = set.getInst(*current + 1);
			uint8_t tgtArray = set.getInst(*current + 2);
			uint8_t index = set.getInst(*current + 3);

			if (!registerReference_[tgtArray]) {
				VM_PRINTF_FATAL("Target array register %i is not a reference\n",
						tgtArray);
			}

			SP<VMEntryType> arrayType = heap_.getType(registers_[tgtArray]);

			if (!arrayType->isArray()) {
				VM_PRINTF_FATAL("%s",
						"Target register is not a reference to an array\n");
			}

			int size = arrayType->arraySubtype()->getElementSize();

			uint8_t* dataPtr =
					heap_.getAddress(registers_[tgtArray])
							+ (registers_[index]
									* ((long) arrayType->arraySubtype()->getElementSize()));

			uint8_t* max = heap_.getAddress(registers_[tgtArray])
					+ heap_.getSize(registers_[tgtArray]);

			if (dataPtr > max) {
				VM_PRINTF_FATAL("%s", "VM Array out of bounds exception\n");
			}

			switch (size) {

			case 1:
				*dataPtr = registers_[data];
				break;

			case 2:
				*(uint16_t*) (dataPtr) = registers_[data];
				break;

			case 4:
				*(uint32_t*) (dataPtr) = registers_[data];
				break;

			case 8:
				*(uint64_t*) (dataPtr) = registers_[data];
				break;

			default:
				VM_PRINTF_FATAL("%i is an unsupported move size\n", size);
				break;
			}

			*current += vmOpCodeSize;
			break;
		}

		case OpArrayGet: {

			uint8_t tgtArray = set.getInst(*current + 1);
			uint8_t index = set.getInst(*current + 2);
			uint8_t dataRegister = set.getInst(*current + 3);

			if (!registerReference_[tgtArray]) {
				VM_PRINTF_FATAL("%s", "Register is not a reference\n");
			}

			SP<VMEntryType> arrayType = heap_.getType(registers_[tgtArray]);

			if (!arrayType->isArray()) {

				VM_PRINTF_FATAL("%s",
						"Register is not a reference to an array\n");

			}

			int size = arrayType->arraySubtype()->getElementSize();

			uint8_t* dataPtr =
					heap_.getAddress(registers_[tgtArray])
							+ (registers_[index]
									* ((long) arrayType->arraySubtype()->getElementSize()));
			uint8_t* max = heap_.getAddress(registers_[tgtArray])
					+ heap_.getSize(registers_[tgtArray]);

			if (dataPtr > max) {
				VM_PRINTF_FATAL("%s", "VM Array out of bounds exception\n");
			}

			switch (size) {

			case 1:
				registers_[dataRegister] = *dataPtr;
				break;

			case 2:
				registers_[dataRegister] = *(uint16_t*) (dataPtr);
				break;

			case 4:
				registers_[dataRegister] = *(uint32_t*) (dataPtr);
				break;

			case 8:
				registers_[dataRegister] = *(uint64_t*) (dataPtr);
				break;

			default:
				VM_PRINTF_FATAL("%i is an unsupported move size\n", size);
				break;

			}

			registerReference_[dataRegister] =
					arrayType->arraySubtype()->isReference();

			*current += vmOpCodeSize;
			break;
		}

		case OpNewArray: {

			//Get the arguments
			uint8_t lengthRegister = set.getInst(*current + 1);
			uint8_t destinationRegister = set.getInst(*current + 2);
			int constantLocation = set.getInst(*current + 3);

			//Get the type
			std::string type = (char const*) set.getConstantString(
					constantLocation);

			//Find the type.
			auto typeSearch = findType(type);

			if (typeSearch.Null()) {
				VM_PRINTF_FATAL("Type %s not found\n", type.c_str());
			}

			//Check the type is an array
			if (!typeSearch->isArray()) {
				VM_PRINTF_FATAL("%s", "Cannot create valid array from type\n");
			}

			//Check that the length register is a number
			if (registerReference_[lengthRegister]) {
				VM_PRINTF_FATAL("%s",
						"Length register should not be a reference\n");
			}

			long length = registers_[lengthRegister]
					* typeSearch->arraySubtype()->getElementSize();

			uint8_t* initial = new uint8_t[length];
			memset(initial, 0, length);

			registers_[destinationRegister] = heap_.allocate(typeSearch, length,
					initial);

			registerReference_[destinationRegister] = true;

			delete[] initial;

			VM_PRINTF_LOG("Allocated and created %li\n",
					registers_[destinationRegister]);

			*current += vmOpCodeSize;

			gcStat_++;

			break;
		}

		case OpCallFn: {
			uint8_t modeRegister = set.getInst(*current + 1);
			char* name = 0;

			if (modeRegister == Constant) {

				name = set.getConstantString(set.getInt(*current + 2));

			} else {

				uint8_t reg = set.getConstantByte(*current + 2);
				long heapEntry = registers_[reg];

				if (!heap_.validReference(heapEntry)) {
					VM_PRINTF_FATAL(
							"Entry %li is not a valid heap entry for function call\n",
							heapEntry);
				}

				name = (char*) heap_.getAddress(heapEntry);
			}

			VM_PRINTF_LOG("Calling function %s\n", name);

			long currentBack = *current;
			execute(name);
			*current = currentBack;

			*current += vmOpCodeSize;
			break;
		}

		case OpReturn: {
			VM_PRINTF_DBG("VM Return at instruction %li\n", *current);
			shouldReturn = true;
			break;
		}

		default: {
			printf("Invalid instruction %li. %li\n", *current,
					set.getInst(*current));
			return;
		}

		}

		if (gcStat_ > GarbageCollectHitLimit) {
			garbageCollection();
			gcStat_ = 0;
		}

	}

	printState();
}

void VirtualMachine::pushRegister(uint8_t reg) {

	if (registerReference_[reg]) {
		markStackReference();
	}

	pushStackLong(registers_[reg]);
}

void VirtualMachine::garbageCollection() {

	VM_PRINTF_WARN("%s\n", "TODO: GC CHECK STACK");
	VM_PRINTF_WARN("%s\n", "TODO: GC CHECK HEAP");

	VM_PRINTF_LOG("%s\n", "Garbage collector running");

	std::vector<long> toInvestigate;
	toInvestigate.clear();

	heap_.unflagAll();

	for (unsigned int i = 0; i < vmNumRegisters; ++i) {

		if (registerReference_[i] && heap_.validReference(registers_[i])) {
			heap_.flag(registers_[i]);
			toInvestigate.push_back(registers_[i]);
		}

	}

	for (unsigned int i = 0; i < toInvestigate.size(); ++i) {

		long next = toInvestigate[i];

		if (!heap_.validReference(next)) {
			VM_PRINTF_FATAL("ERROR: Reference at register %i is not valid\n",
					i);
		}

		SP<VMEntryType> nextType = heap_.getType(next);

		if (nextType.Null()) {
			VM_PRINTF_FATAL("%s", "ERROR: Heap type failure\n");
		}

		//If it is an array check if it is an array of references and if it is flag and check every reference.
		if (nextType->isArray()) {

			SP<VMEntryType> subtype = nextType->arraySubtype();

			if (subtype->isReference()) {

				uint8_t* dataOriginal = heap_.getAddress(next);
				long* data = (long*) dataOriginal;

				//Loop a pointer between the start and end of the data
				while (((uint8_t*) data) < (dataOriginal + heap_.getSize(next))) {

					//Don't flag nullptrs
					if (*data != 0) {
						heap_.flag(*data);
						toInvestigate.push_back(*data);
					}

					data++;
				}

			}

		} else if (nextType->isReference()) {
			printf("Is a reference\n");
			long ref = *(long*) (heap_.getAddress(next));
			heap_.flag(ref);
			toInvestigate.push_back(ref);
		}

	}

	int numDeleted = heap_.deleteUnflagged();
	VM_PRINTF_LOG("Garbage collector done deleting %i elements\n", numDeleted);
}

void VirtualMachine::printState() {

	VM_PRINTF_LOG("%s", "--VM STATE--\n");

	for (unsigned int i = 0; i < registers_[vmStackCurrentPointer]; i++) {
		VM_PRINTF_LOG("%x ", stack_[i]);
	}

	VM_PRINTF_LOG("%s", "\n");

	for (unsigned int i = 0; i < vmNumRegisters; i += 3) {

		if (i < vmNumRegisters) {
			VM_PRINTF_LOG("#%i:%li ", i, registers_[i]);
		}

		if (i + 1 < vmNumRegisters) {
			VM_PRINTF_LOG("#%i:%li ", i + 1, registers_[i + 1]);
		}

		if (i + 2 < vmNumRegisters) {
			VM_PRINTF_LOG("#%i:%li", i + 2, registers_[i + 2]);
		}

		VM_PRINTF_LOG("%s", "\n");
	}

	VM_PRINTF_LOG("%s\n", heap_.debugState().c_str());

	VM_PRINTF_LOG("%s", "--VM STATE END--\n");
}

long VirtualMachine::stackLong(long pos) {
	return *((long*) stack_ + pos);
}

void VirtualMachine::stackSetLong(long pos, long v) {
	*((long*) stack_ + pos) = v;
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

void VirtualMachine::pushStackLong(long v) {
	stackSetLong(registers_[vmStackCurrentPointer], v);
	registers_[vmStackCurrentPointer] += 8;
}

/**
 * Mark the next entry pushed to the stack as a reference
 */
void VirtualMachine::markStackReference() {
	stackReferences_.push_back(registers_[vmStackCurrentPointer]);
}

} /* namespace VM */
