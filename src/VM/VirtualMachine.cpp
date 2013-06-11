/*
 * VirtualMachine.cpp
 *
 *  Created on: 28 May 2013
 *      Author: blake
 */

#include "VirtualMachine.hpp"
#include <Value/Int.hpp>
#include <Statement/Heap.hpp>
#include <stdio.h>

namespace VM {

VirtualMachine::VirtualMachine() {
	registers_ = new long[vmNumRegisters];

	for (unsigned int i = 0; i < vmNumRegisters; ++i) {
		registers_[i] = 0;
	}
}

VirtualMachine::~VirtualMachine() {
	// TODO Auto-generated destructor stub
}

void VirtualMachine::execute(InstructionSet& set) {

	registers_[vmProgramCounter] = set.startInstruction();
	long* current = &registers_[vmProgramCounter];

	while (*current < set.numInstructions()) {

		switch (set.getInst(*current)) {

		case OpAddLong: {

			uint8_t left = set.getInst(*current + 1);
			uint8_t right = set.getInst(*current + 2);

			registers_[left] = registers_[left] + registers_[right];

			*current += 3;
			break;
		}

		case OpTestEqual: {

			uint8_t target = set.getInst(*current + 1);
			uint8_t left = set.getInst(*current + 2);
			uint8_t right = set.getInst(*current + 3);

			if (registers_[left] == registers_[right]) {
				registers_[vmProgramCounter] = registers_[target];
			} else {
				*current += 4;
			}

			break;
		}

		case OpTestNotEqual: {

			uint8_t target = set.getInst(*current + 1);
			uint8_t left = set.getInst(*current + 2);
			uint8_t right = set.getInst(*current + 3);

			if (registers_[left] != registers_[right]) {
				registers_[vmProgramCounter] = registers_[target];
			} else {
				*current += 4;
			}

			break;
		}

		case OpTestLongEqual: {

			uint8_t target = set.getInst(*current + 1);
			uint8_t left = set.getInst(*current + 2);
			long testValue = set.getLong(*current + 3);

			if (registers_[left] == testValue) {
				registers_[vmProgramCounter] = registers_[target];
			} else {
				*current += 11;
			}

			break;
		}

		case OpTestLongNotEqual: {

			uint8_t target = set.getInst(*current + 1);
			uint8_t left = set.getInst(*current + 2);
			long testValue = set.getLong(*current + 3);

			if (registers_[left] != testValue) {
				registers_[vmProgramCounter] = registers_[target];
			} else {
				*current += 11;
			}

			break;
		}

		case OpLoadRegister: {

			uint8_t reg = set.getInst(*current + 1);
			long data = set.getLong(*current + 2);

			registers_[reg] = data;
			*current = *current + 10;
			break;
		}

		case OpMoveRegister: {

			uint8_t source = set.getInst(*current + 1);
			uint8_t target = set.getInst(*current + 2);
			registers_[target] = registers_[source];
			*current = *current + 3;
			break;
		}

		case OpJumpRegister: {
			uint8_t reg = set.getInst(*current + 1);
			registers_[vmProgramCounter] = registers_[reg];
			break;
		}

		case OpPushLongRegister: {
			uint8_t reg = set.getInst(*current + 1);
			stack_.pushLong(registers_[reg]);
			*current += 2;
			break;
		}

		case OpPopLongRegister: {

			uint8_t reg = set.getInst(*current + 1);

			printf("Register %i\n", reg);

			registers_[reg] = stack_.popLong();
			*current += 2;
			break;
		}

			/*
			 case OpPop: {
			 stack_.pop();
			 *current = *current + 1;
			 break;
			 }

			 case OpPopRegister: {
			 registers_[code[*current].data] = stack_.pop();
			 *current = *current + 1;
			 break;
			 }*/

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

	for (unsigned int i = 0; i < stack_.size(); i++) {
		printf("%x ", stack_.getByte(i));
	}

	printf("\n");

	for (unsigned int i = 0; i < vmNumRegisters / 3; i++) {
		printf("#%i:%li #%i:%li #%i:%li\n", i, registers_[i],
				i + vmNumRegisters / 3, registers_[i + vmNumRegisters / 3],
				i + (2 * vmNumRegisters / 3),
				registers_[i + (2 * vmNumRegisters / 3)]);
	}

	printf("--VM STATE END--\n");
}

} /* namespace VM */
