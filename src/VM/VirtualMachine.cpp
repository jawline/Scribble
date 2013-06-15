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

namespace VM {

VirtualMachine::VirtualMachine() {
	registers_ = new long[vmNumRegisters];

	for (unsigned int i = 0; i < vmNumRegisters; ++i) {
		registers_[i] = 0;
	}

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
			*current += vmOpCodeSize;
			break;
		}

		case OpReturn: {
			shouldReturn = true;
			break;
		}

		case OpJump: {

			uint8_t mode = set.getInst(*current + 1);
			int dest = set.getInt(*current + 2);

			switch (mode) {

			case DirectRelative:
				*current += (dest * vmOpCodeSize);
				break;

			case DirectExact:
				*current = (dest * vmOpCodeSize);
				break;

			case RegisterRelative:
				*current += (registers_[dest] * vmOpCodeSize);
				break;

			case RegisterExact:
				*current = (registers_[dest] * vmOpCodeSize);
				break;

			}

			break;
		}

		case OpAdd: {

			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);
			uint8_t dest = set.getInst(*current + 3);

			registers_[dest] = registers_[left] + registers_[right];

			*current += vmOpCodeSize;
			break;
		}

		case OpTestEqual: {
			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);

			if (registers_[left] == registers_[right]) {
				*current += vmOpCodeSize;
			} else {
				*current += 2 * vmOpCodeSize;
			}

			break;
		}

		case OpTestNotEqual: {
			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);

			if (registers_[left] != registers_[right]) {
				*current += vmOpCodeSize;
			} else {
				*current += 2 * vmOpCodeSize;
			}

			break;
		}


		case OpLoadConstant: {

			uint8_t reg = set.getInst(*current + 1);
			int constant = set.getInt(*current + 2);

			switch (set.getConstantByte(constant)) {

			case CInt:
				registers_[reg] = set.getConstantInt(constant + 1);
				break;

			case CLong:
				registers_[reg] = set.getConstantLong(constant + 1);
				break;

			default:
				printf("Unhandled load\n");
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

	}

	printState();
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

	printf("--VM STATE END--\n");
}

} /* namespace VM */
