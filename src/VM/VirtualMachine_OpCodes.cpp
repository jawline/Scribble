#include "VirtualMachine.hpp"
#include "OpCodes.hpp"
#include "JumpTypes.hpp"
#include "Constants.hpp"
#include "VirtualMachine_Debug.hpp"

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
