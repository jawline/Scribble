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
#include "VirtualMachine_Debug.hpp"
#include <API/Function.hpp>
#include <stdio.h>

namespace VM {

VirtualMachine::VirtualMachine() :
		currentInstruction(0), stackBasePointer(0), stackCurrentPointer(0) {

	//Allocate memory for registers
	registers_ = new int64_t[vmNumRegisters];
	registerReference_ = new bool[vmNumRegisters];

	//Initialize all the registers
	for (unsigned int i = 0; i < vmNumRegisters; ++i) {
		registers_[i] = 0;
		registerReference_[i] = false;
	}

	//Register all the primitive types
	registerEntry("char",
			NamespaceEntry(
					SmartPointer < VMEntryType
							> (new VMEntryType("char", 1, false))));

	registerEntry("bool",
			NamespaceEntry(
					SmartPointer < VMEntryType
							> (new VMEntryType("bool", 1, false))));

	registerEntry("short",
			NamespaceEntry(
					SmartPointer < VMEntryType
							> (new VMEntryType("short", 2, false))));

	registerEntry("int",
			NamespaceEntry(
					SmartPointer < VMEntryType
							> (new VMEntryType("int", 4, false))));

	registerEntry("float32",
			NamespaceEntry(
					SmartPointer < VMEntryType
							> (new VMEntryType("float32", 4, false))));

	registerEntry("long",
			NamespaceEntry(
					SmartPointer < VMEntryType
							> (new VMEntryType("int", 8, false))));

	registerEntry("string",
			NamespaceEntry(
					SmartPointer < VMEntryType
							> (new VMEntryType("string",
									namespace_.find("char").getTypeReference()))));

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

SmartPointer<VMEntryType> VirtualMachine::findType(std::string& name) {

	NamespaceEntry entry;

	//If the namespace entry is not found in the namespace
	if (!VM::NamespaceEntry::searchNamespace(namespace_, name, entry)) {

		//If it starts with 'array(' try to generate it from existing types
		char const* prefix = "array(";

		if (strncmp(prefix, name.c_str(), strlen(prefix)) == 0) {

			std::string subtypeName = name.substr(strlen(prefix),
					name.size() - strlen(prefix) - 1);
			SmartPointer<VMEntryType> subtype = findType(subtypeName);

			if (subtype.get() == nullptr) {
				VM_PRINTF_FATAL("Cannot create array of invalid subtype %s\n",
						subtypeName.c_str());
				return nullptr;
			}

			SmartPointer<VMEntryType> entryType = SmartPointer<VMEntryType>(new VMEntryType(name, subtype));
			registerEntry(name, entryType);
			VM_PRINTF_LOG("Generating new type %s\n", name.c_str());
			return entryType;
		}

		//If it does not start with array then return NULL so that the VM error handler can catch it
		return nullptr;
	}

	//If the entry in the namespace specified is not a type then return null
	if (entry.getType() != Type) {
		return nullptr;
	}

	return entry.getTypeReference();
}

bool VirtualMachine::returnToPreviousFunction(
		SmartPointer<VMFunc>& currentFunction, InstructionSet& set) {

			if (currentVmState_.size() > 0) {

				VMState top = currentVmState_.top();
				currentVmState_.pop();

				currentFunction = top.func_;
				set = currentFunction->getInstructions();
				currentInstruction = top.pc_;

				return true;
			} else {
				return false;
			}
		}

void VirtualMachine::execute(std::string function) {

	NamespaceEntry functionEntry;
	SmartPointer<VMFunc> currentFunction;

	if (!VM::NamespaceEntry::searchNamespace(namespace_, function,
			functionEntry) || functionEntry.getType() != Function) {
		VM_PRINTF_FATAL("%s is not a registered function\n", function.c_str());
	}

	currentFunction = functionEntry.getFunction();

	if (currentFunction->isNative()) {
		currentFunction->getFunction()->execute(this);
		return;
	}

	InstructionSet instructionSet = currentFunction->getInstructions();

	currentInstruction = instructionSet.startInstruction();

	bool shouldReturn = false;

	while (!shouldReturn) {

		//If the current PC is above the number of instructions in this function then attempt to return. Else execute the instruction at the PC.
		if (currentInstruction >= instructionSet.numInstructions()) {

			if (!returnToPreviousFunction(currentFunction, instructionSet)) {
				shouldReturn = true;
			}

		} else {

			switch (instructionSet.getInst(currentInstruction)) {

			/**
			 *  Loads the constant data at the specified constant index into the given register.
			 *  Capable of loading elements into the heap and assigning their reference if their initial data is already known ( Such as pushing strings ).
			 */

			case OpLoadConstant: {

				int constantDataStart = instructionSet.getInt(
						currentInstruction + 1);
				uint8_t destinationRegister = instructionSet.getInst(
						currentInstruction + 5);

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

				case CFloat32:

					*((float32_t*) &registers_[destinationRegister]) =
							instructionSet.getConstantFloat32(
									constantDataStart + 1);
					registerReference_[destinationRegister] = false;
					break;

				case CArray: {

					//Read in the type of array from the constant data with this instruction set.
					std::string type = instructionSet.getConstantString(
							constantDataStart + 1);

					//Check the type is valid
					if (namespace_.find(type).getType() != Type) {
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
							namespace_.find(type).getTypeReference(), sizeBytes,
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

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Copy whatever is in the target register into the destination register copying over whether it is a reference or not.
				 */

			case OpMove: {
				uint8_t target = instructionSet.getInst(currentInstruction + 1);
				uint8_t dest = instructionSet.getInst(currentInstruction + 2);
				registers_[dest] = registers_[target];
				registerReference_[dest] = registerReference_[target];
				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Jump to a different instruction
				 */

			case OpJump: {

				uint8_t mode = instructionSet.getInst(currentInstruction + 1);
				int dest = instructionSet.getInt(currentInstruction + 2);

				switch (mode) {

				case DirectRelative: {
					long dOld = currentInstruction;
					long dRest = ((long) dest) * ((long) vmOpCodeSize);
					dOld = dOld + dRest;
					currentInstruction = dOld;
					//VM_PRINTF_LOG("Jump direct relative to %li\n", ((long) dest));
					break;
				}

				case DirectExact:
					currentInstruction =
							(((long) dest) * ((long) vmOpCodeSize));
					break;

				case RegisterRelative:
					currentInstruction += (registers_[dest]
							* ((long) vmOpCodeSize));
					break;

				case RegisterExact:
					currentInstruction = (registers_[dest]
							* ((long) vmOpCodeSize));
					break;

				}

				break;
			}

				/**
				 * Add the left and right registers and place the result in the dest register.
				 */

			case OpAdd: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);
				uint8_t dest = instructionSet.getInst(currentInstruction + 3);

				//	VM_PRINTF_LOG("Added registers %i and %i. Placing result in %i\n",
				//			left, right, dest);

				registers_[dest] = registers_[left] + registers_[right];
				registerReference_[dest] = false;

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Subtract the left and right registers and place the result in the dest register.
				 */

			case OpSub: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);
				uint8_t dest = instructionSet.getInst(currentInstruction + 3);

				//VM_PRINTF_LOG(
				//	"Subtracted registers %i and %i. Placing result in %i\n",
				//left, right, dest);

				registers_[dest] = registers_[left] - registers_[right];
				registerReference_[dest] = false;

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Multiply the left and right registers and place the result in the dest register.
				 */

			case OpMul: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);
				uint8_t dest = instructionSet.getInst(currentInstruction + 3);

				//VM_PRINTF_LOG(
				//		"Multiplied registers %i and %i. Placing result in %i\n",
				//		left, right, dest);

				registers_[dest] = registers_[left] * registers_[right];
				registerReference_[dest] = false;

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Divide the left and right registers and place the result in the dest register.
				 */

			case OpDiv: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);
				uint8_t dest = instructionSet.getInst(currentInstruction + 3);

				//VM_PRINTF_LOG("Divided registers %i and %i. Placing result in %i\n",
				//		left, right, dest);

				registers_[dest] = registers_[left] / registers_[right];
				registerReference_[dest] = false;

				currentInstruction += vmOpCodeSize;
				break;
			}

			case OpInc: {
				uint8_t dst = instructionSet.getInst(currentInstruction + 1);
				registers_[dst] = registers_[dst] + 1;
				currentInstruction += vmOpCodeSize;
				break;
			}

			case OpDec: {
				uint8_t dst = instructionSet.getInst(currentInstruction + 1);
				registers_[dst] = registers_[dst] - 1;
				currentInstruction += vmOpCodeSize;
				break;
			}

			case OpAddFloat32: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);
				uint8_t dest = instructionSet.getInst(currentInstruction + 3);

				//	VM_PRINTF_LOG("Added registers %i and %i. Placing result in %i\n",
				//			left, right, dest);

				float32_t* index = (float32_t*) &registers_[dest];
				float32_t* leftR = (float32_t*) &registers_[left];
				float32_t* rightR = (float32_t*) &registers_[right];

				*index = *leftR + *rightR;

				registerReference_[dest] = false;

				currentInstruction += vmOpCodeSize;
				break;
			}

			case OpSubFloat32: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);
				uint8_t dest = instructionSet.getInst(currentInstruction + 3);

				//VM_PRINTF_LOG(
				//	"Subtracted registers %i and %i. Placing result in %i\n",
				//left, right, dest);

				float32_t* index = (float32_t*) &registers_[dest];
				float32_t* leftR = (float32_t*) &registers_[left];
				float32_t* rightR = (float32_t*) &registers_[right];
				*index = *leftR - *rightR;

				registerReference_[dest] = false;

				currentInstruction += vmOpCodeSize;
				break;
			}

			case OpMulFloat32: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);
				uint8_t dest = instructionSet.getInst(currentInstruction + 3);

				//VM_PRINTF_LOG(
				//		"Multiplied registers %i and %i. Placing result in %i\n",
				//		left, right, dest);

				float32_t* index = (float32_t*) &registers_[dest];
				float32_t* leftR = (float32_t*) &registers_[left];
				float32_t* rightR = (float32_t*) &registers_[right];
				*index = *leftR * *rightR;

				registerReference_[dest] = false;

				currentInstruction += vmOpCodeSize;
				break;
			}

			case OpDivFloat32: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);
				uint8_t dest = instructionSet.getInst(currentInstruction + 3);

				//VM_PRINTF_LOG("Divided registers %i and %i. Placing result in %i\n",
				//		left, right, dest);

				float32_t* index = (float32_t*) &registers_[dest];
				float32_t* leftR = (float32_t*) &registers_[left];
				float32_t* rightR = (float32_t*) &registers_[right];
				*index = *leftR / *rightR;

				registerReference_[dest] = false;

				currentInstruction += vmOpCodeSize;
				break;
			}

			case OpCmpFloat32: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);
				uint8_t dest = instructionSet.getInst(currentInstruction + 3);

				float32_t* leftR = (float32_t*) &registers_[left];
				float32_t* rightR = (float32_t*) &registers_[right];

				if (*leftR == *rightR) {
					registers_[dest] = 0;
				} else if (*leftR > *rightR) {
					registers_[dest] = 1;
				} else {
					registers_[dest] = -1;
				}

				registerReference_[dest] = false;

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Test if two registers are equal. If true then execute the next instruction else skip it.
				 */

			case OpEqual: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);

				if (registers_[left] == registers_[right]) {
					currentInstruction += vmOpCodeSize;
				} else {
					currentInstruction += 2 * vmOpCodeSize;
				}

				break;
			}

			case OpNotEqual: {

				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);

				if (registers_[left] != registers_[right]) {
					currentInstruction += vmOpCodeSize;
				} else {
					currentInstruction += 2 * vmOpCodeSize;
				}

				break;
			}

			case OpEqualZero: {
				uint8_t tReg = instructionSet.getInst(currentInstruction + 1);

				if (registers_[tReg] == 0) {
					currentInstruction += vmOpCodeSize;
				} else {
					currentInstruction += vmOpCodeSize * 2;
				}

				break;
			}

				/**
				 *  Test if one register is less than another. If true execute next instruction otherwise skip it.
				 */

			case OpLessThan: {
				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);

				if (registers_[left] < registers_[right]) {
					currentInstruction += vmOpCodeSize;
				} else {
					currentInstruction += 2 * vmOpCodeSize;
				}

				break;
			}

			case OpGreaterThan: {
				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);

				if (registers_[left] > registers_[right]) {
					currentInstruction += vmOpCodeSize;
				} else {
					currentInstruction += 2 * vmOpCodeSize;
				}

				break;
			}

			case OpGreaterThanOrEqual: {
				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);

				if (registers_[left] >= registers_[right]) {
					currentInstruction += vmOpCodeSize;
				} else {
					currentInstruction += 2 * vmOpCodeSize;
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
				uint8_t startRegister = instructionSet.getInst(
						currentInstruction + 1);
				uint8_t numRegisters = instructionSet.getInst(
						currentInstruction + 2);

				//printf("Pushing from %i registers from %i\n", numRegisters, startRegister);

				for (uint8_t i = startRegister;
						i < startRegister + numRegisters; i++) {
					pushRegister(i);
				}

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Pop n registers starting from the start+nth register and the last pop acting on the start register
				 */
			case OpPopRegisters: {
				uint8_t startRegister = instructionSet.getInst(
						currentInstruction + 1);
				uint8_t numRegisters = instructionSet.getInst(
						currentInstruction + 2);

//				VM_PRINTF_LOG("Popping from %i registers from %i\n", ((int)numRegisters), ((int)startRegister));

				for (uint8_t i = (startRegister + numRegisters);
						i > startRegister; i--) {
					popStackLong(registers_[i - 1], registerReference_[i - 1]);
				}

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Pop a long from the stack and ignore it ( Don't put it in any registers ).
				 */

			case OpPopNil: {

				int64_t t;
				bool r;

				popStackLong(t, r);

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Test whether the register left's value is <= than the register right.
				 * If true execute the next instruction
				 * Else skip the next function.
				 */

			case OpLessThanOrEqual: {
				uint8_t left = instructionSet.getInst(currentInstruction + 1);
				uint8_t right = instructionSet.getInst(currentInstruction + 2);

				if (registers_[left] <= registers_[right]) {
					currentInstruction += vmOpCodeSize;
				} else {
					currentInstruction += 2 * vmOpCodeSize;
				}

				break;
			}

			case OpStructGetField: {

				uint8_t tgtArray = instructionSet.getInst(
						currentInstruction + 1);
				uint8_t indexReg = instructionSet.getInst(
						currentInstruction + 2);
				uint8_t dataReg = instructionSet.getInst(
						currentInstruction + 3);

				//Check that the target array is a valid reference
				if (!registerReference_[tgtArray]) {
					VM_PRINTF_FATAL(
							"Target array register %i is not a reference\n",
							tgtArray);
				}

				//Check that the array type is a structure
				SmartPointer<VMEntryType> arrayType = heap_.getType(registers_[tgtArray]);

				if (arrayType->getBaseType() != VM::VMStructure) {
					VM_PRINTF_FATAL("%s",
							"Target register is not a reference to an array\n");
				}

				//Check that the index is valid
				if (registers_[indexReg] < 0
						|| registers_[indexReg]
								>= arrayType->getStructureFields().size()) {
					VM_PRINTF_FATAL(
							"Index %i is not a valid index to the structure. The structure only takes %i elements\n",
							indexReg, arrayType->getStructureFields().size());
				}

				//Get the VM type of the field being set and the offset of it in bytes in the structure data.
				SmartPointer<VMEntryType> type = arrayType->getStructureFields()[registers_[indexReg]]->getType();
				unsigned int offset = arrayType->getStructureFieldOffset(
						registers_[indexReg]);

				//Get a pointer to the element by getting the start of the structure and adding the element bytes offset
				int8_t* elementData = (int8_t*) getHeap().getAddress(
						registers_[tgtArray]) + offset;

				switch (type->getElementSize()) {

				case 1:
					registers_[dataReg] = (int64_t) (*elementData);
					break;
				case 2:
					registers_[dataReg] = (int64_t) (*((int16_t*) elementData));
					break;
				case 4:
					registers_[dataReg] = (int64_t) (*((int32_t*) elementData));
					break;
				case 8:
					registers_[dataReg] = (int64_t) (*((int64_t*) elementData));
					break;
				}

				//After getting the data check if the data got was a reference. If it was then mark it as one.
				registerReference_[dataReg] = type->isReference();

				currentInstruction += vmOpCodeSize;

				break;
			}

			case OpStructSetField: {

				uint8_t tgtArray = instructionSet.getInst(
						currentInstruction + 1);
				uint8_t indexReg = instructionSet.getInst(
						currentInstruction + 2);
				uint8_t dataReg = instructionSet.getInst(
						currentInstruction + 3);

				//Check that the target array is a valid reference
				if (!registerReference_[tgtArray]) {
					VM_PRINTF_FATAL(
							"Target array register %i is not a reference\n",
							tgtArray);
				}

				//Check that the array type is a structure
				SmartPointer<VMEntryType> arrayType = heap_.getType(registers_[tgtArray]);

				if (arrayType->getBaseType() != VM::VMStructure) {
					VM_PRINTF_FATAL("%s",
							"Target register is not a reference to an array\n");
				}

				//Check that the index is valid
				if (registers_[indexReg] < 0
						|| registers_[indexReg]
								>= arrayType->getStructureFields().size()) {

					VM_PRINTF_FATAL(
							"Index %li is not a valid index to the structure. The structure only takes %li elements\n",
							(long int)registers_[indexReg], (long int)arrayType->getStructureFields().size());

				}

				//Get the VM type of the field being set and the offset of it in bytes in the structure data.
				SmartPointer<VMEntryType> type = arrayType->getStructureFields()[registers_[indexReg]]->getType();

				unsigned int offset = arrayType->getStructureFieldOffset(
						registers_[indexReg]);

				//Get a pointer to the element by getting the start of the structure and adding the element bytes offset
				int8_t* elementData = (int8_t*) getHeap().getAddress(
						registers_[tgtArray]) + offset;

				switch (type->getElementSize()) {

				case 1:
					*elementData = (int8_t) registers_[dataReg];
				case 2:
					*((int16_t*) elementData) = (int16_t) registers_[dataReg];
				case 4:
					*((int32_t*) elementData) = (int32_t) registers_[dataReg];
				case 8:
					*((int64_t*) elementData) = (int64_t) registers_[dataReg];
					break;

				}

				currentInstruction += vmOpCodeSize;

				break;
			}

				/**
				 * Set the specified element in the target array to the given data value.
				 */

			case OpArraySet: {

				uint8_t data = instructionSet.getInst(currentInstruction + 1);
				uint8_t tgtArray = instructionSet.getInst(
						currentInstruction + 2);
				uint8_t index = instructionSet.getInst(currentInstruction + 3);

				if (!registerReference_[tgtArray]) {
					VM_PRINTF_FATAL(
							"Target array register %i is not a reference\n",
							tgtArray);
				}

				SmartPointer<VMEntryType> arrayType = heap_.getType(registers_[tgtArray]);

				if (arrayType->getBaseType() != VM::VMArray) {
					VM_PRINTF_FATAL("%s",
							"Target register is not a reference to an array\n");
				}

				int size = arrayType->arraySubtype()->getElementSize();

				long offsetBytes = registers_[index]
						* arrayType->arraySubtype()->getElementSize();

				uint8_t* dataPtr = heap_.getAddress(registers_[tgtArray])
						+ offsetBytes;

				uint8_t* max = heap_.getAddress(registers_[tgtArray])
						+ heap_.getSize(registers_[tgtArray]);

				if (dataPtr > max) {

					VM_PRINTF_FATAL(
							"VM Array out of bounds exception accessing index %li offset %i element size %i size %i max %li\n",
							(long int)registers_[index], (int)offsetBytes, (int)arrayType->arraySubtype()->getElementSize(), (int)heap_.getSize(registers_[tgtArray]), (long int)max);

				}

				switch (size) {

				case 1:
					*(int8_t*) (dataPtr) = registers_[data];
					break;

				case 2:
					*(int16_t*) (dataPtr) = registers_[data];
					break;

				case 4:
					*(int32_t*) (dataPtr) = registers_[data];
					break;

				case 8:
					*(int64_t*) (dataPtr) = registers_[data];
					break;

				default:
					VM_PRINTF_FATAL("%i is an unsupported move size\n", size);
					break;
				}

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Set the dataRegisters value to be the value of the array at the specified index.
				 */

			case OpArrayGet: {

				uint8_t tgtArray = instructionSet.getInst(
						currentInstruction + 1);
				uint8_t index = instructionSet.getInst(currentInstruction + 2);
				uint8_t dataRegister = instructionSet.getInst(
						currentInstruction + 3);

				if (!registerReference_[tgtArray]) {
					this->printState();
					VM_PRINTF_FATAL("Register %i is not a reference\n",
							tgtArray);
				}

				SmartPointer<VMEntryType> arrayType = heap_.getType(registers_[tgtArray]);

				if (arrayType->getBaseType() != VM::VMArray) {

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
							"VM Array out of bounds exception accessing index %li offset %i element size %i size %i\n",
							(long int ) registers_[index], (int)offsetBytes, (int)arrayType->arraySubtype()->getElementSize(), (int)heap_.getSize(registers_[tgtArray]));

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

				currentInstruction += vmOpCodeSize;
				break;
			}

			case OpNewStruct: {

				int constantLocation = instructionSet.getInt(
						currentInstruction + 1);
				uint8_t dest = instructionSet.getInst(currentInstruction + 5);

				//Get the type
				std::string type =
						(char const*) instructionSet.getConstantString(
								constantLocation);

				//Find the type.
				auto typeSearch = findType(type);

				if (typeSearch.get() == nullptr) {
					VM_PRINTF_FATAL("Structure type %s is not registered\n",
							type.c_str());
				}

				if (typeSearch->getBaseType() != VMStructure) {
					VM_PRINTF_FATAL("Namespace entry %s is not a structure\n",
							type.c_str());
				}

				registers_[dest] = getHeap().allocate(typeSearch,
						typeSearch->getStructureSize(), 0);

				registerReference_[dest] = true;

				VM_PRINTF_LOG(
						"Allocated %i bytes for type %s and placed reference in register %i\n",
						typeSearch->getStructureSize(), type.c_str(), dest);

				currentInstruction += vmOpCodeSize;
				gcStat_++;

				break;
			}

				/**
				 * Create a new array of the specified type ( Stored in constants ) and length ( The value of lengthRegister ) and set its reference to the specified register.
				 */

			case OpNewArray: {

				//Get the arguments
				uint8_t lengthRegister = instructionSet.getInst(
						currentInstruction + 1);

				uint8_t destinationRegister = instructionSet.getInst(
						currentInstruction + 2);

				int constantLocation = instructionSet.getInt(
						currentInstruction + 3);

				//Get the type
				std::string type =
						(char const*) instructionSet.getConstantString(
								constantLocation);

				//Find the type.
				auto typeSearch = findType(type);

				if (typeSearch.get() == nullptr) {
					VM_PRINTF_FATAL("Array Type %s is not registered\n",
							type.c_str());
				}

				//Check the type is an array
				if (typeSearch->getBaseType() != VM::VMArray) {
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

				registers_[destinationRegister] = heap_.allocate(typeSearch,
						length, nullptr);

				registerReference_[destinationRegister] = true;

				VM_PRINTF_LOG(
						"Allocated and created new array %li of size %li\n",
						(long int)registers_[destinationRegister], (long int)registers_[lengthRegister]);

				currentInstruction += vmOpCodeSize;

				gcStat_++;

				break;
			}

				/**
				 * Set the value of dest register to be the length of the array pointed to by the value of the array length register.
				 */

			case OpArrayLength: {

				//Get the register which has the reference to the array.
				uint8_t arrayRegister = instructionSet.getInst(
						currentInstruction + 1);

				//Get the register in which the length should be put
				uint8_t dest = instructionSet.getInst(currentInstruction + 2);

				//Check it's a valid reference
				if (!registerReference_[arrayRegister]
						|| !heap_.validReference(registers_[arrayRegister])) {
					VM_PRINTF_FATAL(
							"Register %i not not a reference (OpArrayLength)\n",
							arrayRegister);
				}

				//Check that it is an array
				if (heap_.getType(registers_[arrayRegister])->getBaseType()
						!= VM::VMArray) {
					VM_PRINTF_FATAL("%s",
							"Reference is not an array (OpArrayLength)\n");
				}

				//Return the size in bytes divided by the element size of an index in the array to get the size of the array.
				registers_[dest] =
						(heap_.getSize(registers_[arrayRegister])
								/ heap_.getType(registers_[arrayRegister])->arraySubtype()->getElementSize());

				currentInstruction += vmOpCodeSize;
				break;
			}

				/**
				 * Call the specified function. Two modes Constant or Heap. If Constant mode name of function is stored in constant instruction set zone otherwise name of function is pointed to by string in heap specified by register.
				 */

			case OpCallFn: {

				uint8_t modeRegister = instructionSet.getInst(
						currentInstruction + 1);
				std::string name;

				if (modeRegister == Constant) {

					name = instructionSet.getConstantString(
							instructionSet.getInt(currentInstruction + 2));

				} else {

					uint8_t reg = instructionSet.getConstantByte(
							currentInstruction + 2);
					long heapEntry = registers_[reg];

					if (!heap_.validReference(heapEntry)) {
						VM_PRINTF_FATAL(
								"Entry %li is not a valid heap entry for function call\n",
								heapEntry);
					}

					name = (char*) heap_.getAddress(heapEntry);
				}

				//VM_PRINTF_LOG("Calling function %s\n", name);

				if (!VM::NamespaceEntry::searchNamespace(namespace_, name,
						functionEntry) || functionEntry.getType() != Function) {

					VM_PRINTF_FATAL("%s is not a registered function\n",
							name.c_str());

				}

				if (functionEntry.getFunction()->isNative()) {
					functionEntry.getFunction()->getFunction()->execute(this);
					currentInstruction += vmOpCodeSize;
				} else {

					//Otherwise push the VM state and then setup the new function. Set the return PC to be the current PC plus vmOpCodeSize
					currentVmState_.push(
							VMState(currentFunction,
									(currentInstruction) + vmOpCodeSize));

					currentFunction = functionEntry.getFunction();

					instructionSet = currentFunction->getInstructions();
					currentInstruction = instructionSet.startInstruction();

				}

				break;
			}

				/**
				 * Return to the previous function that was running or exit.
				 */

			case OpReturn: {

				//VM_PRINTF_DBG("VM Return at instruction %li\n", currentInstruction);

				if (!returnToPreviousFunction(currentFunction,
						instructionSet)) {
					shouldReturn = true;
				}

				break;
			}

			default: {
				VM_PRINTF_FATAL("Invalid instruction %li. %ii\n",
						currentInstruction, instructionSet.getInst(currentInstruction));
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

	//As the function exits run the garbage collector and reset the GC stat value
	garbageCollection();
	gcStat_ = 0;

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

		SmartPointer<VMEntryType> nextType = heap_.getType(next);

		if (nextType.get() == nullptr) {
			VM_PRINTF_FATAL("%s", "ERROR: Heap type failure\n");
		}

		//If it is an array check if it is an array of references and if it is flag and check every reference.
		if (nextType->getBaseType() == VM::VMArray) {

			SmartPointer<VMEntryType> subtype = nextType->arraySubtype();

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

		} else if (nextType->getBaseType() == VMStructure) {

			//For every field in the structure
			for (unsigned int i = 0; i < nextType->getStructureFields().size(); i++) {

				//If that field is a reference to anything on the heap
				if (nextType->getStructureFields()[i]->getType()->isReference()) {

					//Get a pointer to the structure data
					uint8_t* structurePtr = heap_.getAddress(next);

					//Get a pointer to the reference within the structure
					long* referencePtr = (long*) (structurePtr + nextType->getStructureFieldOffset(i));

					//If we aren't looking at a null pointer
					if (*referencePtr != 0) {
						heap_.flag(*referencePtr);
						toInvestigate.push_back(*referencePtr);
					}

				}

			}

		} else if (nextType->isReference()) {
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

	for (unsigned int i = 0; i < stackCurrentPointer; i++) {
		VM_PRINTF_LOG("%x ", stack_[i]);
	}

	VM_PRINTF_LOG("%s", "\n");

	for (unsigned int i = 0; i < vmNumRegisters; i += 3) {

		if (i < vmNumRegisters) {
			VM_PRINTF_LOG("#%i:%li ", i, (long int)registers_[i]);
		}

		if (i + 1 < vmNumRegisters) {
			VM_PRINTF_LOG("#%i:%li ", i + 1, (long int)registers_[i + 1]);
		}

		if (i + 2 < vmNumRegisters) {
			VM_PRINTF_LOG("#%i:%li", i + 2, (long int)registers_[i + 2]);
		}

		VM_PRINTF_LOG("%s", "\n");
	}

	VM_PRINTF_LOG("%s\n", heap_.debugState().c_str());

	VM_PRINTF_LOG("%s", "--VM STATE END--\n");
}

void VirtualMachine::logMessage(VMLogLevel level, std::string message) {
	switch (level) {

	case Log: {
		VM_PRINTF_LOG("%s", message.c_str());
		break;
	}

	case Debug: {
		VM_PRINTF_DBG("%s", message.c_str());
		break;
	}

	case Warn: {
		VM_PRINTF_WARN("%s", message.c_str());
		break;
	}

	case Fatal: {
		VM_PRINTF_FATAL("%s", message.c_str());
		break;
	}

	}
}

} /* namespace VM */
