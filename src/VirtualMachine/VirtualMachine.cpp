#include "VirtualMachine.hpp"
#include <version_info.hpp>

int VirtualMachine::lastInstanceID__ = 0;

VirtualMachine::VirtualMachine() {

	vmID_ = ++lastInstanceID__;
	printf("%s %i.%i.%i VM ID %i instantiated\n", PROJECT_NAME, VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, vmID_);
	running_ = false;
}

VirtualMachine::~VirtualMachine() {
	printf("VM ID %i destructed\n", vmID_);
}

void VirtualMachine::setInstructions(SP<InstructionList> code) {
	printf("VM ID %i change in instruction set\n", vmID_);
	currentCode_ = code;
}

void VirtualMachine::execute() {

	printf("Executing VM ID %i\n", vmID_);
	position_ = 0;
	running_ = true;

	while (running_ && position_ < currentCode_->length()) {

		unsigned char opcode = currentCode_->getChar(position_);
		
		switch (opcode) {

			case LoadConst: {
				position_++;
				unsigned char variableType = currentCode_->getChar(position_);
				position_++;

				int val = currentCode_->getInt(position_);
				printf("V: %i\n", val);

				position_ += sizeof(int);

				break;
			}

			case NoOp: {
				printf("VM %i NoOp\n", vmID_);
				position_++;
				break;
			}

			default: {
				printf("Error in VM %i: OpCode %i is not a valid code\n", vmID_, opcode);
				return;
			}
		}

	}

	printf("VM %i finished execution\n", vmID_);
}
