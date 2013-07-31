/*
 * VirtualMachine.cpp
 *
 *  Created on: 28 May 2013
 *      Author: blake
 */

#include "VirtualMachine.hpp"
#include "OpCodes.hpp"
#include "JumpTypes.hpp"
#include "ConstantTypes.hpp"
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

	registeredTypes_["char"] = new VMEntryType("char", 1, false);
	registeredTypes_["int"] = new VMEntryType("int", 4, false);
	registeredTypes_["long"] = new VMEntryType("int", 8, false);
	registeredTypes_["array(int)"] = new VMEntryType("array(int)",
			registeredTypes_["int"]);

	registeredTypes_["string"] = new VMEntryType("string",
			registeredTypes_["char"]);

	stack_ = new uint8_t[4086];
}

VirtualMachine::~VirtualMachine() {
	// TODO Auto-generated destructor stub
}

void VirtualMachine::execute(InstructionSet& set) {

	registers_[vmProgramCounter] = set.startInstruction();
	long* current = &registers_[vmProgramCounter];
	bool shouldReturn = false;

	while (!shouldReturn && *current < set.numInstructions()) {

		switch (set.getInst(*current)) {

		case OpMove: {
			uint8_t target = set.getInst(*current + 1);
			uint8_t dest = set.getInst(*current + 2);
			registers_[dest] = registers_[target];
			registerReference_[dest] = registerReference_[target];
			VM_PRINTF_LOG("VM Move %i to %i %i to %i\n", target, dest, registerReference_[dest], registerReference_[target]);
			*current += vmOpCodeSize;
			break;
		}

		case OpReturn: {
			VM_PRINTF_DBG("VM Return at instruction %li\n", *current);
			shouldReturn = true;
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
				VM_PRINTF_FATAL("Target array register %i is not a reference\n", tgtArray);
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
			auto typeSearch = registeredTypes_.find(type);

			if (typeSearch == registeredTypes_.end()) {
				VM_PRINTF_FATAL("Type %s not found\n", type.c_str());
			}

			if (!typeSearch->second->isArray()) {
				VM_PRINTF_FATAL("%s", "Cannot create valid array from type\n");
			}


			if (registerReference_[lengthRegister]) {
				VM_PRINTF_FATAL("%s",
						"Length register should not be a reference\n");
			}

			long length = registers_[lengthRegister] * typeSearch->second->arraySubtype()->getElementSize();


			uint8_t* initial = new uint8_t[length];
			memset(initial, 0, length);

			registers_[destinationRegister] = heap_.allocate(typeSearch->second,
					length, initial);

			registerReference_[destinationRegister] = true;

			delete[] initial;

			printf("DEST %i\n", destinationRegister);

			VM_PRINTF_LOG("Allocated and created %li\n",
					registers_[destinationRegister]);

			*current += vmOpCodeSize;

			break;
		}

		case OpLoadConstant: {

			int constant = set.getInt(*current + 1);
			uint8_t reg = set.getInst(*current + 5);

			switch (set.getConstantByte(constant)) {

			case CInt:
				registers_[reg] = set.getConstantInt(constant + 1);
				registerReference_[reg] = false;
				break;

			case CLong:
				registers_[reg] = set.getConstantLong(constant + 1);
				registerReference_[reg] = false;
				break;

			case CArray: {

				printf("ARRAY LOAD\n");

				std::string type = set.getConstantString(constant + 1);

				printf("Type %s\n", type.c_str());

				int next = constant + 2 + type.size();

				//Get the size of the area to create
				int sizeBytes = set.getConstantInt(next);

				next += 4;

				int sizeStored = set.getConstantInt(next);

				printf("Size: %i\n", sizeBytes);

				next += 4;

				printf("Data: ");

				uint8_t* initial = new uint8_t[sizeBytes];
				memset(initial, 0, sizeBytes);

				for (int i = 0; i < sizeStored; ++i) {
					initial[i] = set.getConstantByte(next);
					next++;
					printf("%c", initial[i]);
				}

				printf("\n");

				registers_[reg] = heap_.allocate(registeredTypes_[type],
						sizeBytes, initial);

				delete[] initial;

				registerReference_[reg] = true;
				break;
			}

			default:
				printf("Unhandled load %i\n", set.getConstantByte(constant));
				break;

			}

			*current += vmOpCodeSize;
			break;
		}

		default: {
			printf("Invalid instruction %li. %li\n", *current,
					set.getInst(*current));
			return;
		}

		}

		garbageCollection();
	}

	printState();
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
						data++;
					}

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

	printf("--VM STATE--\n");

	for (unsigned int i = 0; i < registers_[vmStackCurrentPointer]; i++) {
		printf("%x ", stack_[i]);
	}

	printf("\n");

	for (unsigned int i = 0; i < vmNumRegisters; i += 3) {

		if (i < vmNumRegisters) {
			printf("#%i:%li ", i, registers_[i]);
		}

		if (i + 1 < vmNumRegisters) {
			printf("#%i:%li ", i + 1, registers_[i + 1]);
		}

		if (i + 2 < vmNumRegisters) {
			printf("#%i:%li", i + 2, registers_[i + 2]);
		}

		printf("\n");
	}

	printf("%s\n", heap_.debugState().c_str());

	printf("--VM STATE END--\n");
}

} /* namespace VM */
