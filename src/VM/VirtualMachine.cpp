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

#define VM_PRINTF_FATAL(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__); this->printState(); do { } while (1)

/**
 * Loads a given function into entry and executes if native. NOTE: DO NOT USE OUTSIDE OF VM::execute
 */
#define VM_LOAD_FUNC(fn, entry) 	if (!VM::searchNamespace(namespace_, fn, entry) || entry.getType() != Function) { VM_PRINTF_FATAL("%s is not a registered function\n", fn.c_str()); } if (entry.getFunction().isNative()) { entry.getFunction().getFunction()->execute(this); }

#if VM_DEBUG == 3
FILE* flog = fopen("VMLogFile", "w");
#define VM_PRINTF_DBG(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#define VM_PRINTF_WARN(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#define VM_PRINTF_LOG(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#elif VM_DEBUG == 2
FILE* flog = fopen("VMLogFile", "w");
#define VM_PRINTF_DBG(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#define VM_PRINTF_WARN(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#define VM_PRINTF_LOG(fmt, ...)
#elif VM_DEBUG == 1
FILE* flog = fopen("VMLogFile", "w");
#define VM_PRINTF_DBG(fmt, ...)
#define VM_PRINTF_WARN(fmt, ...) fprintf(flog, fmt, __VA_ARGS__) fflush(flog);
#define VM_PRINTF_LOG(fmt, ...)
#else
#define VM_PRINTF_WARN(fmt, ...)
#define VM_PRINTF_DBG(fmt, ...)
#define VM_PRINTF_LOG(fmt, ...)
#endif

namespace VM {

VirtualMachine::VirtualMachine() {

	//Allocate memory for registers
	registers_ = new long[vmNumRegisters];
	registerReference_ = new bool[vmNumRegisters];

	//Initialize all the registers
	for (unsigned int i = 0; i < vmNumRegisters; ++i) {
		registers_[i] = 0;
		registerReference_[i] = false;
	}

	//Register all the primitive types
	registerEntry("char", NamespaceEntry(new VMEntryType("char", 1, false)));
	registerEntry("bool", NamespaceEntry(new VMEntryType("bool", 1, false)));
	registerEntry("short", NamespaceEntry(new VMEntryType("short", 2, false)));
	registerEntry("int", NamespaceEntry(new VMEntryType("int", 4, false)));
	registerEntry("long", NamespaceEntry(new VMEntryType("int", 8, false)));

	registerEntry("string",
			NamespaceEntry(
					new VMEntryType("string",
							namespace_["char"].getTypeReference())));

	//Allocate the stack
	stack_ = new uint8_t[vmStackIncrease];

	//Initialize the stack height
	currentStackHeight_ = vmStackIncrease;

	//Initialize garbage collection variables.
	gcStat_ = 0;
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
				VM_PRINTF_FATAL("Cannot create array of invalid subtype %s\n",
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

bool VirtualMachine::returnToPreviousFunction(InstructionSet& instructionSet) {

	if (currentVmState_.size() > 0) {
		VMState top = currentVmState_.top();
		currentVmState_.pop();
		instructionSet = top.set_;
		registers_[VM::vmProgramCounter] = top.pc_;
		return true;
	} else {
		return false;
	}
}

void VirtualMachine::execute(std::string function) {

	NamespaceEntry functionEntry;

	VM_LOAD_FUNC(function, functionEntry);

	if (functionEntry.getFunction().isNative()) {
		return;
	}

	InstructionSet instructionSet =
			functionEntry.getFunction().getInstructions();

	registers_[vmProgramCounter] = instructionSet.startInstruction();
	long* current = &registers_[vmProgramCounter];
	bool shouldReturn = false;

	while (!shouldReturn) {

		//If the current PC is above the number of instructions in this function then attempt to return. Else execute the instruction at the PC.
		if (*current >= instructionSet.numInstructions()) {

			if (!returnToPreviousFunction(instructionSet)) {
				shouldReturn = true;
			}

		} else {

			switch (instructionSet.getInst(*current)) {

			/**
			 *  Loads the constant data at the specified constant index into the given register.
			 *  Capable of loading elements into the heap and assigning their reference if their initial data is already known ( Such as pushing strings ).
			 */

			case OpLoadConstant: {

				int constantDataStart = instructionSet.getInt(*current + 1);
				uint8_t destinationRegister = instructionSet.getInst(
						*current + 5);

//			VM_PRINTF_LOG("Loading constant into %i\n", destinationRegister);

				switch (instructionSet.getConstantByte(constantDataStart)) {

				case CInt:
					registers_[destinationRegister] =
							instructionSet.getConstantInt(
									constantDataStart + 1);
					registerReference_[destinationRegister] = false;
					break;

				case CLong:
					registers_[destinationRegister] =
							instructionSet.getConstantLong(
									constantDataStart + 1);
					registerReference_[destinationRegister] = false;
					break;

				case CArray: {

					//Read in the type of array from the constant data with this instruction set.
					std::string type = instructionSet.getConstantString(
							constantDataStart + 1);

					//Check the type is valid
					if (namespace_[type].getType() != Type) {
						VM_PRINTF_FATAL("Invalid type %s\n", type.c_str());
					}

					//Essentially a pointer to the next constant bit to read
					int next = constantDataStart + 2 + type.size();

					//Get the size of the area to create
					int sizeBytes = instructionSet.getConstantInt(next);
					next += 4;

					//Get the size stored. Will be filled from the start. Any remaining space will be zero'd
					int sizeStored = instructionSet.getConstantInt(next);
					next += 4;

					uint8_t* initial = new uint8_t[sizeBytes];

					//Cheap optimization. As you know that this data is about to be written don't wipe the array from the start but instead wipe it from the end of the area
					memset(initial + sizeStored, 0, sizeBytes - sizeStored);

					for (int i = 0; i < sizeStored; ++i) {
						initial[i] = instructionSet.getConstantByte(next);
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
							instructionSet.getConstantByte(constantDataStart));
					break;

				}

				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Copy whatever is in the target register into the destination register copying over whether it is a reference or not.
				 */

			case OpMove: {
				uint8_t target = instructionSet.getInst(*current + 1);
				uint8_t dest = instructionSet.getInst(*current + 2);
				registers_[dest] = registers_[target];
				registerReference_[dest] = registerReference_[target];
				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Jump to a different instruction
				 */

			case OpJump: {

				uint8_t mode = instructionSet.getInst(*current + 1);
				int dest = instructionSet.getInt(*current + 2);

				switch (mode) {

				case DirectRelative: {
					long dOld = *current;
					long dRest = ((long) dest) * ((long) vmOpCodeSize);
					dOld = dOld + dRest;
					*current = dOld;
					//VM_PRINTF_LOG("Jump direct relative to %li\n", ((long) dest));
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

				/**
				 * Add the left and right registers and place the result in the dest register.
				 */

			case OpAdd: {

				uint8_t left = instructionSet.getInst(*current + 1);
				uint8_t right = instructionSet.getInst(*current + 2);
				uint8_t dest = instructionSet.getInst(*current + 3);

				//	VM_PRINTF_LOG("Added registers %i and %i. Placing result in %i\n",
				//			left, right, dest);

				registers_[dest] = registers_[left] + registers_[right];
				registerReference_[dest] = false;

				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Subtract the left and right registers and place the result in the dest register.
				 */

			case OpSub: {

				uint8_t left = instructionSet.getInst(*current + 1);
				uint8_t right = instructionSet.getInst(*current + 2);
				uint8_t dest = instructionSet.getInst(*current + 3);

				//VM_PRINTF_LOG(
				//	"Subtracted registers %i and %i. Placing result in %i\n",
				//left, right, dest);

				registers_[dest] = registers_[left] - registers_[right];
				registerReference_[dest] = false;

				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Multiply the left and right registers and place the result in the dest register.
				 */

			case OpMul: {

				uint8_t left = instructionSet.getInst(*current + 1);
				uint8_t right = instructionSet.getInst(*current + 2);
				uint8_t dest = instructionSet.getInst(*current + 3);

				//VM_PRINTF_LOG(
				//		"Multiplied registers %i and %i. Placing result in %i\n",
				//		left, right, dest);

				registers_[dest] = registers_[left] * registers_[right];
				registerReference_[dest] = false;

				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Divide the left and right registers and place the result in the dest register.
				 */

			case OpDiv: {

				uint8_t left = instructionSet.getInst(*current + 1);
				uint8_t right = instructionSet.getInst(*current + 2);
				uint8_t dest = instructionSet.getInst(*current + 3);

				//VM_PRINTF_LOG("Divided registers %i and %i. Placing result in %i\n",
				//		left, right, dest);

				registers_[dest] = registers_[left] / registers_[right];
				registerReference_[dest] = false;

				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Test if two registers are equal. If true then execute the next instruction else skip it.
				 */

			case OpEqual: {

				uint8_t left = instructionSet.getInst(*current + 1);
				uint8_t right = instructionSet.getInst(*current + 2);

				if (registers_[left] == registers_[right]) {
					*current += vmOpCodeSize;
				} else {
					*current += 2 * vmOpCodeSize;
				}

				break;
			}

				/**
				 *  Test if one register is less than another. If true execute next instruction otherwise skip it.
				 */

			case OpLessThan: {
				uint8_t left = instructionSet.getInst(*current + 1);
				uint8_t right = instructionSet.getInst(*current + 2);

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
				uint8_t startRegister = instructionSet.getInst(*current + 1);
				uint8_t numRegisters = instructionSet.getInst(*current + 2);

				//printf("Pushing from %i registers from %i\n", numRegisters, startRegister);

				for (uint8_t i = startRegister;
						i < startRegister + numRegisters; i++) {
					pushRegister(i);
				}

				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Pop n registers starting from the start+nth register and the last pop acting on the start register
				 */
			case OpPopRegisters: {
				uint8_t startRegister = instructionSet.getInst(*current + 1);
				uint8_t numRegisters = instructionSet.getInst(*current + 2);

				//printf("Popping from %i registers from %i\n", ((int)numRegisters), ((int)startRegister));

				for (uint8_t i = (startRegister + numRegisters) - 1;
						i >= startRegister; i--) {
					popStackLong(registers_[i], registerReference_[i]);
				}

				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Pop a long from the stack and ignore it ( Don't put it in any registers ).
				 */

			case OpPopNil: {

				long t;
				bool r;

				popStackLong(t, r);

				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Test whether the register left's value is <= than the register right.
				 * If true execute the next instruction
				 * Else skip the next function.
				 */

			case OpLessThanOrEqual: {
				uint8_t left = instructionSet.getInst(*current + 1);
				uint8_t right = instructionSet.getInst(*current + 2);

				if (registers_[left] <= registers_[right]) {
					*current += vmOpCodeSize;
				} else {
					*current += 2 * vmOpCodeSize;
				}

				break;
			}

				/**
				 * Set the specified element in the target array to the given data value.
				 */

			case OpArraySet: {

				uint8_t data = instructionSet.getInst(*current + 1);
				uint8_t tgtArray = instructionSet.getInst(*current + 2);
				uint8_t index = instructionSet.getInst(*current + 3);

				if (!registerReference_[tgtArray]) {
					VM_PRINTF_FATAL(
							"Target array register %i is not a reference\n",
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

				/**
				 * Set the dataRegisters value to be the value of the array at the specified index.
				 */

			case OpArrayGet: {

				uint8_t tgtArray = instructionSet.getInst(*current + 1);
				uint8_t index = instructionSet.getInst(*current + 2);
				uint8_t dataRegister = instructionSet.getInst(*current + 3);

				if (!registerReference_[tgtArray]) {
					this->printState();
					VM_PRINTF_FATAL("Register %i is not a reference\n",
							tgtArray);
				}

				SP<VMEntryType> arrayType = heap_.getType(registers_[tgtArray]);

				if (!arrayType->isArray()) {

					VM_PRINTF_FATAL(
							"Register %i is not a reference to an array\n",
							tgtArray);

				}

				int size = arrayType->arraySubtype()->getElementSize();

				long offsetBytes = registers_[index]
						* arrayType->arraySubtype()->getElementSize();

				uint8_t* dataPtr = heap_.getAddress(registers_[tgtArray])
						+ offsetBytes;

				uint8_t* max = heap_.getAddress(registers_[tgtArray])
						+ heap_.getSize(registers_[tgtArray]);

				if (dataPtr >= max) {
					VM_PRINTF_FATAL(
							"VM Array out of bounds exception accessing index %li offset %i element size %i size %i data pointer %li max %li\n",
							registers_[index], offsetBytes, arrayType->arraySubtype()->getElementSize(), heap_.getSize(registers_[tgtArray]), dataPtr, max);
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

				/**
				 * Create a new array of the specified type ( Stored in constants ) and length ( The value of lengthRegister ) and set its reference to the specified register.
				 */

			case OpNewArray: {

				//Get the arguments
				uint8_t lengthRegister = instructionSet.getInst(*current + 1);
				uint8_t destinationRegister = instructionSet.getInst(
						*current + 2);
				int constantLocation = instructionSet.getInt(*current + 3);

				//Get the type
				std::string type =
						(char const*) instructionSet.getConstantString(
								constantLocation);

				//Find the type.
				auto typeSearch = findType(type);

				if (typeSearch.Null()) {
					VM_PRINTF_FATAL("Type %s is not registered\n",
							type.c_str());
				}

				//Check the type is an array
				if (!typeSearch->isArray()) {
					VM_PRINTF_FATAL("%s",
							"Cannot create valid array from type\n");
				}

				//Check that the length register is a number
				if (registerReference_[lengthRegister]) {
					VM_PRINTF_FATAL("%s",
							"Length register should not be a reference\n");
				}

				//Check that the desired length is valid
				if (registers_[lengthRegister] < 1) {
					VM_PRINTF_FATAL("%s",
							"Cannot allocate array of length < 1");
				}

				long length = registers_[lengthRegister]
						* typeSearch->arraySubtype()->getElementSize();

				uint8_t* initial = new uint8_t[length];
				memset(initial, 0, length);

				registers_[destinationRegister] = heap_.allocate(typeSearch,
						length, initial);

				registerReference_[destinationRegister] = true;

				delete[] initial;

				VM_PRINTF_LOG(
						"Allocated and created new array %li of size %li\n",
						registers_[destinationRegister], registers_[lengthRegister]);

				*current += vmOpCodeSize;

				gcStat_++;

				break;
			}

				/**
				 * Set the value of dest register to be the length of the array pointed to by the value of the array length register.
				 */

			case OpArrayLength: {

				//Get the register which has the reference to the array.
				uint8_t arrayRegister = instructionSet.getInst(*current + 1);

				//Get the register in which the length should be put
				uint8_t dest = instructionSet.getInst(*current + 2);

				//Check it's a valid reference
				if (!registerReference_[arrayRegister]
						|| !heap_.validReference(registers_[arrayRegister])) {
					VM_PRINTF_FATAL(
							"Register %i not not a reference (OpArrayLength)\n",
							arrayRegister);
				}

				//Check that it is an array
				if (!heap_.getType(registers_[arrayRegister])->isArray()) {
					VM_PRINTF_FATAL("%s",
							"Reference is not an array (OpArrayLength)\n");
				}

				//Return the size in bytes divided by the element size of an index in the array to get the size of the array.
				registers_[dest] =
						(heap_.getSize(registers_[arrayRegister])
								/ heap_.getType(registers_[arrayRegister])->arraySubtype()->getElementSize());

				*current += vmOpCodeSize;
				break;
			}

				/**
				 * Call the specified function. Two modes Constant or Heap. If Constant mode name of function is stored in constant instruction set zone otherwise name of function is pointed to by string in heap specified by register.
				 */

			case OpCallFn: {

				uint8_t modeRegister = instructionSet.getInst(*current + 1);
				char* name = 0;

				if (modeRegister == Constant) {

					name = instructionSet.getConstantString(
							instructionSet.getInt(*current + 2));

				} else {

					uint8_t reg = instructionSet.getConstantByte(*current + 2);
					long heapEntry = registers_[reg];

					if (!heap_.validReference(heapEntry)) {
						VM_PRINTF_FATAL(
								"Entry %li is not a valid heap entry for function call\n",
								heapEntry);
					}

					name = (char*) heap_.getAddress(heapEntry);
				}

				VM_PRINTF_LOG("Calling function %s\n", name);

				NamespaceEntry entry;
				VM_LOAD_FUNC(std::string(name), entry);

				//If it is native then the load will have already executed and the PC just needs incrementing
				if (entry.getFunction().isNative()) {
					*current += vmOpCodeSize;
				} else {
					//Otherwise push the VM state and then setup the new function. Set the return PC to be the current PC plus vmOpCodeSize
					currentVmState_.push(
							VMState(instructionSet, (*current) + vmOpCodeSize));
					instructionSet = entry.getFunction().getInstructions();
					*current = instructionSet.startInstruction();
				}

				break;
			}

				/**
				 * Return to the previous function that was running or exit.
				 */

			case OpReturn: {

				VM_PRINTF_DBG("VM Return at instruction %li\n", *current);

				if (!returnToPreviousFunction(instructionSet)) {
					shouldReturn = true;
				}

				break;
			}

			default: {
				VM_PRINTF_FATAL("Invalid instruction %li. %li\n",
						*current, instructionSet.getInst(*current));
				return;
			}

			}

			//After each instruction check the gcStat and
			//if it has hit the hit limit then run the garbage collector.

			if (gcStat_ > GarbageCollectHitLimit) {
				garbageCollection();
				gcStat_ = 0;
			}

		}

	}

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

	//Loop through all registers flagging any references found and adding them to a list of references to explore
	for (unsigned int i = 0; i < vmNumRegisters; ++i) {

		if (registerReference_[i] && heap_.validReference(registers_[i])) {
			heap_.flag(registers_[i]);
			toInvestigate.push_back(registers_[i]);
		}

	}

	//Flag every reference on the stack and add it to the list of objects to investigate.
	for (unsigned int i = 0; i < stackReferences_.size(); i++) {
		heap_.flag(stackLong(stackReferences_[i]));
		toInvestigate.push_back(stackLong(stackReferences_[i]));
	}

	//Investigate every flagged object. Flagging anything that they may reference
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

	//After everything delete what remains
	int numDeleted = heap_.processUnflagged();

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

void VirtualMachine::expandStack() {

	VM_PRINTF_LOG("Increased stack size by %i blocks to %li",
			vmStackIncrement, currentStackHeight_);

	//Allocate memory for a larger stack
	uint8_t* newStack = new uint8_t[currentStackHeight_ + vmStackIncrease];

	//Copy over and then free up the existing stack
	memcpy(newStack, stack_, currentStackHeight_);
	delete[] stack_;

	//Change the stack to the new stack
	stack_ = newStack;
	currentStackHeight_ += vmStackIncrease;

}

void VirtualMachine::pushStackLong(long v) {

	while (registers_[vmStackCurrentPointer] >= currentStackHeight_) {
		expandStack();
	}

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
