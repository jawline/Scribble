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
	// TODO Auto-generated constructor stub

}

VirtualMachine::~VirtualMachine() {
	// TODO Auto-generated destructor stub
}

void VirtualMachine::execute(unsigned int start,
		std::vector<Instruction> code) {

	unsigned int current = start;

	while (current < code.size()) {

		switch (code[current].code) {

		case NoOp: {
			printf("NoOp\n");
			current++;
			break;
		}

		case OpPush: {
			stack_.push(code[current].data->clone());
			current++;
			break;
		}

		case OpPop: {
			valueHeap.free(stack_.pop());
			current++;
			break;
		}

		case OpJump: {
			current = ((IntValue*)code[current].data)->value();
			break;
		}

		case OpAdd: {

			Value* rhs = stack_.pop();
			Value* lhs = stack_.pop();

			lhs->applyOperator(Add, rhs);
			valueHeap.free(rhs);

			stack_.push(lhs);

			current++;
			break;
		}

		case OpSub: {

			Value* rhs = stack_.pop();
			Value* lhs = stack_.pop();

			lhs->applyOperator(Subtract, rhs);
			valueHeap.free(rhs);

			stack_.push(lhs);

			current++;
			break;
		}

		case OpMul: {
			Value* rhs = stack_.pop();
			Value* lhs = stack_.pop();

			lhs->applyOperator(Multiply, rhs);
			valueHeap.free(rhs);

			stack_.push(lhs);

			current++;
			break;

		}

		case OpDiv: {
			Value* rhs = stack_.pop();
			Value* lhs = stack_.pop();

			lhs->applyOperator(Divide, rhs);
			valueHeap.free(rhs);

			stack_.push(lhs);

			current++;
			break;

		}

		default: {
			printf("Invalid instruction.\n");
			return;
		}

		}

	}

}

} /* namespace VM */
