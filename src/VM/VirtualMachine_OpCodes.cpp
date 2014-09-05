#include "VirtualMachine.hpp"
#include "OpCodes.hpp"
#include "JumpTypes.hpp"
#include "Constants.hpp"
#include "VirtualMachine_Debug.hpp"
#include <API/Function.hpp>

namespace VM {

void VirtualMachine::opMove(InstructionSet& instructionSet) {
	uint8_t target = instructionSet.getByte(currentInstruction + 1);
	uint8_t dest = instructionSet.getByte(currentInstruction + 2);
	registers_[dest] = registers_[target];
	registerReference_[dest] = registerReference_[target];
	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opInc(InstructionSet& instructionSet) {
	uint8_t dst = instructionSet.getByte(currentInstruction + 1);
	registers_[dst] = registers_[dst] + 1;
	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opDec(InstructionSet& instructionSet) {
	uint8_t dst = instructionSet.getByte(currentInstruction + 1);
	registers_[dst] = registers_[dst] - 1;
	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opNot(InstructionSet& instructionSet) {
	uint8_t reg = instructionSet.getByte(currentInstruction + 1);
	registers_[reg] = !registers_[reg];
	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opAddFloat32(InstructionSet& instructionSet) {
	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);
	uint8_t dest = instructionSet.getByte(currentInstruction + 3);

//	VM_PRINTF_LOG("Added registers %i and %i. Placing result in %i\n",
//			left, right, dest);

	float32_t* index = (float32_t*) &registers_[dest];
	float32_t* leftR = (float32_t*) &registers_[left];
	float32_t* rightR = (float32_t*) &registers_[right];

	*index = *leftR + *rightR;

	registerReference_[dest] = false;

	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opSubFloat32(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);
	uint8_t dest = instructionSet.getByte(currentInstruction + 3);

	//VM_PRINTF_LOG(
	//	"Subtracted registers %i and %i. Placing result in %i\n",
	//left, right, dest);

	float32_t* index = (float32_t*) &registers_[dest];
	float32_t* leftR = (float32_t*) &registers_[left];
	float32_t* rightR = (float32_t*) &registers_[right];
	*index = *leftR - *rightR;

	registerReference_[dest] = false;

	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opMulFloat32(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);
	uint8_t dest = instructionSet.getByte(currentInstruction + 3);

	//VM_PRINTF_LOG(
	//		"Multiplied registers %i and %i. Placing result in %i\n",
	//		left, right, dest);

	float32_t* index = (float32_t*) &registers_[dest];
	float32_t* leftR = (float32_t*) &registers_[left];
	float32_t* rightR = (float32_t*) &registers_[right];
	*index = *leftR * *rightR;

	registerReference_[dest] = false;

	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opDivFloat32(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);
	uint8_t dest = instructionSet.getByte(currentInstruction + 3);

	//VM_PRINTF_LOG("Divided registers %i and %i. Placing result in %i\n",
	//		left, right, dest);

	float32_t* index = (float32_t*) &registers_[dest];
	float32_t* leftR = (float32_t*) &registers_[left];
	float32_t* rightR = (float32_t*) &registers_[right];
	*index = *leftR / *rightR;

	registerReference_[dest] = false;

	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opEqual(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);

	if (registers_[left] == registers_[right]) {
		currentInstruction += vmOpCodeSize;
	} else {
		currentInstruction += 2 * vmOpCodeSize;
	}

}

void VirtualMachine::opEqualZero(InstructionSet& instructionSet) {

	uint8_t tReg = instructionSet.getByte(currentInstruction + 1);

	if (registers_[tReg] == 0) {
		currentInstruction += vmOpCodeSize;
	} else {
		currentInstruction += vmOpCodeSize * 2;
	}

}

void VirtualMachine::opLessThan(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);

	if (registers_[left] < registers_[right]) {
		currentInstruction += vmOpCodeSize;
	} else {
		currentInstruction += 2 * vmOpCodeSize;
	}

}

void VirtualMachine::opGreaterThan(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);

	if (registers_[left] > registers_[right]) {
		currentInstruction += vmOpCodeSize;
	} else {
		currentInstruction += 2 * vmOpCodeSize;
	}

}

void VirtualMachine::opGreaterThanOrEqual(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);

	if (registers_[left] >= registers_[right]) {
		currentInstruction += vmOpCodeSize;
	} else {
		currentInstruction += 2 * vmOpCodeSize;
	}

}

void VirtualMachine::opPushRegisters(InstructionSet& instructionSet) {

	uint8_t startRegister = instructionSet.getByte(currentInstruction + 1);
	uint8_t numRegisters = instructionSet.getByte(currentInstruction + 2);

	//printf("Pushing from %i registers from %i\n", numRegisters, startRegister);
	//VM_PRINTF_LOG("Pushing %i registers from %i\n", numRegisters, startRegister);

	for (uint8_t i = startRegister; i < startRegister + numRegisters; i++) {
		pushRegister(i);
	}

	currentInstruction += vmOpCodeSize;

}

void VirtualMachine::opNotEqual(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);

	if (registers_[left] != registers_[right]) {
		currentInstruction += vmOpCodeSize;
	} else {
		currentInstruction += 2 * vmOpCodeSize;
	}

}

void VirtualMachine::opPopNil(InstructionSet& instructionSet) {
	int64_t t;
	bool r;
	popStackLong(t, r);
	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opLessThanOrEqual(InstructionSet& instructionSet) {
	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);

	if (registers_[left] <= registers_[right]) {
		currentInstruction += vmOpCodeSize;
	} else {
		currentInstruction += 2 * vmOpCodeSize;
	}
}

void VirtualMachine::opNewStruct(InstructionSet& instructionSet) {

	int constantLocation = instructionSet.getInt(currentInstruction + 1);
	uint8_t dest = instructionSet.getByte(currentInstruction + 5);

	//Get the type
	std::string type = (char const*) instructionSet.getConstantString(
			constantLocation);

	//Find the type.
	auto typeSearch = findType(type);

	if (typeSearch.get() == nullptr) {
		VM_PRINTF_FATAL("Structure type %s is not registered\n", type.c_str());
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
}

void VirtualMachine::opArrayLength(InstructionSet& instructionSet) {

	//Get the register which has the reference to the array.
	uint8_t arrayRegister = instructionSet.getByte(currentInstruction + 1);

	//Get the register in which the length should be put
	uint8_t dest = instructionSet.getByte(currentInstruction + 2);

	//Check it's a valid reference
	if (!registerReference_[arrayRegister]
			|| !heap_.validReference(registers_[arrayRegister])) {
		VM_PRINTF_FATAL( "Register %i not not a reference (OpArrayLength)\n",
				arrayRegister);
	}

	//Check that it is an array
	if (heap_.getType(registers_[arrayRegister])->getBaseType()
			!= VM::VMArray) {
		VM_PRINTF_FATAL("%s", "Reference is not an array (OpArrayLength)\n");
	}

	//Return the size in bytes divided by the element size of an index in the array to get the size of the array.
	registers_[dest] =
			(heap_.getSize(registers_[arrayRegister])
					/ heap_.getType(registers_[arrayRegister])->arraySubtype()->getElementSize());

	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opNewArray(InstructionSet& instructionSet) {

	//Get the arguments
	uint8_t lengthRegister = instructionSet.getByte(currentInstruction + 1);

	uint8_t destinationRegister = instructionSet.getByte(
			currentInstruction + 2);

	int constantLocation = instructionSet.getInt(currentInstruction + 3);

	//Get the type
	std::string type = (char const*) instructionSet.getConstantString(
			constantLocation);

	//Find the type.
	auto typeSearch = findType(type);

	if (typeSearch.get() == nullptr) {
		VM_PRINTF_FATAL("Array Type %s is not registered\n", type.c_str());
	}

	//Check the type is an array
	if (typeSearch->getBaseType() != VM::VMArray) {
		VM_PRINTF_FATAL("%s", "Cannot create valid array from type\n");
	}

	//Check that the length register is a number
	if (registerReference_[lengthRegister]) {
		VM_PRINTF_FATAL("%s", "Length register should not be a reference\n");
	}

	//Check that the desired length is valid
	if (registers_[lengthRegister] < 1) {
		VM_PRINTF_FATAL("%s", "Cannot allocate array of length < 1");
	}

	long length = registers_[lengthRegister]
			* typeSearch->arraySubtype()->getElementSize();

	registers_[destinationRegister] = heap_.allocate(typeSearch, length,
			nullptr);

	registerReference_[destinationRegister] = true;

	VM_PRINTF_LOG( "Allocated and created new array %li of size %li\n",
			(long int )registers_[destinationRegister], (long int )registers_[lengthRegister]);

	currentInstruction += vmOpCodeSize;

	gcStat_++;
}

void VirtualMachine::opReturn(InstructionSet& instructionSet) {
	VM_PRINTF_LOG("VM Return at instruction %i\n", currentInstruction);

	if (!returnToPreviousFunction(currentFunction, instructionSet)) {
		shouldReturn = true;
	}

}

void VirtualMachine::opCallFn(InstructionSet& instructionSet) {

	NamespaceEntry functionEntry;

	uint8_t modeRegister = instructionSet.getByte(currentInstruction + 1);
	std::string name;

	if (modeRegister == Constant) {

		name = instructionSet.getConstantString(
				instructionSet.getInt(currentInstruction + 2));

	} else if (modeRegister == Register) {

		uint8_t reg = instructionSet.getByte(currentInstruction + 2);
		long heapEntry = registers_[reg];

		if (!heap_.validReference(heapEntry)) {
			VM_PRINTF_FATAL(
					"Entry %i at register %i is not a valid heap entry for function call\n",
					heapEntry, reg);
		}

		name = (char*) heap_.getAddress(heapEntry);
	}

	VM_PRINTF_LOG("Attempting to call function %s\n", name.c_str());

	if (!VM::NamespaceEntry::searchNamespace(namespace_, name, functionEntry)
			|| functionEntry.getType() != Function) {

		VM_PRINTF_FATAL("%s is not a registered function\n", name.c_str());

	}

	if (functionEntry.getFunction()->isNative()) {
		functionEntry.getFunction()->getFunction()->execute(this);
		currentInstruction += vmOpCodeSize;
	} else {

		//Otherwise push the VM state and then setup the new function. Set the return PC to be the current PC plus vmOpCodeSize
		currentVmState_.push(
				VMState(currentFunction, (currentInstruction) + vmOpCodeSize));

		currentFunction = functionEntry.getFunction();

		instructionSet = currentFunction->getInstructions();
		currentInstruction = instructionSet.getStartLocation();

	}

}

void VirtualMachine::opArrayGet(InstructionSet& instructionSet) {

	uint8_t tgtArray = instructionSet.getByte(currentInstruction + 1);
	uint8_t index = instructionSet.getByte(currentInstruction + 2);
	uint8_t dataRegister = instructionSet.getByte(currentInstruction + 3);

	if (!registerReference_[tgtArray]) {
		this->printState();
		VM_PRINTF_FATAL("Register %i is not a reference\n", tgtArray);
	}

	SmartPointer<VMEntryType> arrayType = heap_.getType(registers_[tgtArray]);

	if (arrayType->getBaseType() != VM::VMArray) {

		VM_PRINTF_FATAL( "Register %i is not a reference to an array\n",
				tgtArray);

	}

	int size = arrayType->arraySubtype()->getElementSize();

	long offsetBytes = registers_[index]
			* arrayType->arraySubtype()->getElementSize();

	uint8_t* dataPtr = heap_.getAddress(registers_[tgtArray]) + offsetBytes;

	uint8_t* max = heap_.getAddress(registers_[tgtArray])
			+ heap_.getSize(registers_[tgtArray]);

	if (dataPtr >= max) {

		VM_PRINTF_FATAL(
				"VM Array out of bounds exception accessing index %li offset %i element size %i size %i\n",
				(long int ) registers_[index], (int )offsetBytes, (int )arrayType->arraySubtype()->getElementSize(), (int )heap_.getSize(registers_[tgtArray]));

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

	registerReference_[dataRegister] = arrayType->arraySubtype()->isReference();

	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opArraySet(InstructionSet& instructionSet) {

	//VM_PRINTF_LOG("%s", "Array set operation\n");

	uint8_t data = instructionSet.getByte(currentInstruction + 1);
	uint8_t tgtArray = instructionSet.getByte(currentInstruction + 2);
	uint8_t index = instructionSet.getByte(currentInstruction + 3);

	if (!registerReference_[tgtArray]) {
		VM_PRINTF_FATAL( "Target array register %i is not a reference\n",
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

	uint8_t* dataPtr = heap_.getAddress(registers_[tgtArray]) + offsetBytes;

	uint8_t* max = heap_.getAddress(registers_[tgtArray])
			+ heap_.getSize(registers_[tgtArray]);

	if (dataPtr > max) {

		VM_PRINTF_FATAL(
				"VM Array out of bounds exception accessing index %li offset %i element size %i size %i max %li\n",
				(long int )registers_[index], (int )offsetBytes, (int )arrayType->arraySubtype()->getElementSize(), (int )heap_.getSize(registers_[tgtArray]), (long int )max);

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
}

void VirtualMachine::opStructSetField(InstructionSet& instructionSet) {

	uint8_t tgtArray = instructionSet.getByte(currentInstruction + 1);
	uint8_t indexReg = instructionSet.getByte(currentInstruction + 2);
	uint8_t dataReg = instructionSet.getByte(currentInstruction + 3);

	//Check that the target array is a valid reference
	if (!registerReference_[tgtArray]) {
		VM_PRINTF_FATAL( "Target array register %i is not a reference\n",
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
					>= (int64_t) arrayType->getStructureFields().size()) {

		VM_PRINTF_FATAL(
				"Index %li is not a valid index to the structure. The structure only takes %li elements\n",
				(long int )registers_[indexReg], (long int )arrayType->getStructureFields().size());

	}

	//Get the VM type of the field being set and the offset of it in bytes in the structure data.
	SmartPointer<VMEntryType> type = arrayType->getStructureFields()[registers_[indexReg]]->getType();

	unsigned int offset = arrayType->getStructureFieldOffset(
			registers_[indexReg]);

	//Get a pointer to the element by getting the start of the structure and adding the element bytes offset
	int8_t* elementData = (int8_t*) getHeap().getAddress(registers_[tgtArray])
			+ offset;

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
}

void VirtualMachine::opStructGetField(InstructionSet& instructionSet) {

	uint8_t tgtArray = instructionSet.getByte(currentInstruction + 1);
	uint8_t indexReg = instructionSet.getByte(currentInstruction + 2);
	uint8_t dataReg = instructionSet.getByte(currentInstruction + 3);

	//Check that the target array is a valid reference
	if (!registerReference_[tgtArray]) {
		VM_PRINTF_FATAL( "Target array register %i is not a reference\n",
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
					>= (int64_t) arrayType->getStructureFields().size()) {
		VM_PRINTF_FATAL(
				"Index %i is not a valid index to the structure. The structure only takes %li elements\n",
				indexReg, (long int )arrayType->getStructureFields().size());
	}

	//Get the VM type of the field being set and the offset of it in bytes in the structure data.
	SmartPointer<VMEntryType> type = arrayType->getStructureFields()[registers_[indexReg]]->getType();
	unsigned int offset = arrayType->getStructureFieldOffset(
			registers_[indexReg]);

	//Get a pointer to the element by getting the start of the structure and adding the element bytes offset
	int8_t* elementData = (int8_t*) getHeap().getAddress(registers_[tgtArray])
			+ offset;

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
}

void VirtualMachine::opPopRegisters(InstructionSet& instructionSet) {

	uint8_t startRegister = instructionSet.getByte(currentInstruction + 1);
	uint8_t numRegisters = instructionSet.getByte(currentInstruction + 2);

	//VM_PRINTF_LOG("Popping %i registers from %i\n", numRegisters, startRegister);

	for (uint8_t i = (startRegister + numRegisters); i > startRegister; i--) {
		popStackLong(registers_[i - 1], registerReference_[i - 1]);
	}

	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opCmpFloat32(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);
	uint8_t dest = instructionSet.getByte(currentInstruction + 3);

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
}

void VirtualMachine::opJump(InstructionSet& instructionSet) {

	uint8_t mode = instructionSet.getByte(currentInstruction + 1);
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
		currentInstruction = (((long) dest) * ((long) vmOpCodeSize));
		break;

	case RegisterRelative:
		currentInstruction += (registers_[dest] * ((long) vmOpCodeSize));
		break;

	case RegisterExact:
		currentInstruction = (registers_[dest] * ((long) vmOpCodeSize));
		break;

	}

}

void VirtualMachine::opAdd(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);
	uint8_t dest = instructionSet.getByte(currentInstruction + 3);

	//	VM_PRINTF_LOG("Added registers %i and %i. Placing result in %i\n",
	//			left, right, dest);

	registers_[dest] = registers_[left] + registers_[right];
	registerReference_[dest] = false;

	currentInstruction += vmOpCodeSize;

}

void VirtualMachine::opLoadConstant(InstructionSet& instructionSet) {

	int constantDataStart = instructionSet.getInt(currentInstruction + 1);
	uint8_t destinationRegister = instructionSet.getByte(
			currentInstruction + 5);

	//			VM_PRINTF_LOG("Loading constant into %i\n", destinationRegister);

	switch (instructionSet.getConstantByte(constantDataStart)) {

	case CInt:
		registers_[destinationRegister] = instructionSet.getConstantInt(
				constantDataStart + 1);
		registerReference_[destinationRegister] = false;
		break;

	case CLong:
		registers_[destinationRegister] = instructionSet.getConstantLong(
				constantDataStart + 1);
		registerReference_[destinationRegister] = false;
		break;

	case CFloat32:

		*((float32_t*) &registers_[destinationRegister]) =
				instructionSet.getConstantFloat32(constantDataStart + 1);
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
				namespace_.find(type).getTypeReference(), sizeBytes, initial);

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

}

void VirtualMachine::opSub(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);
	uint8_t dest = instructionSet.getByte(currentInstruction + 3);

	//VM_PRINTF_LOG(
	//	"Subtracted registers %i and %i. Placing result in %i\n",
	//left, right, dest);

	registers_[dest] = registers_[left] - registers_[right];
	registerReference_[dest] = false;

	currentInstruction += vmOpCodeSize;

}

void VirtualMachine::opDiv(InstructionSet& instructionSet) {
	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);
	uint8_t dest = instructionSet.getByte(currentInstruction + 3);

	//VM_PRINTF_LOG("Divided registers %i and %i. Placing result in %i\n",
	//		left, right, dest);

	registers_[dest] = registers_[left] / registers_[right];
	registerReference_[dest] = false;

	currentInstruction += vmOpCodeSize;
}

void VirtualMachine::opMul(InstructionSet& instructionSet) {

	uint8_t left = instructionSet.getByte(currentInstruction + 1);
	uint8_t right = instructionSet.getByte(currentInstruction + 2);
	uint8_t dest = instructionSet.getByte(currentInstruction + 3);

	//VM_PRINTF_LOG(
	//		"Multiplied registers %i and %i. Placing result in %i\n",
	//		left, right, dest);

	registers_[dest] = registers_[left] * registers_[right];
	registerReference_[dest] = false;

	currentInstruction += vmOpCodeSize;

}

}
