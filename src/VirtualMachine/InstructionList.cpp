#include "InstructionList.hpp"

InstructionList::InstructionList(SP<unsigned char> bytecode, size_t length) {

	bytecode_ = bytecode;
	length_ = length;

}

InstructionList::~InstructionList() {
}
