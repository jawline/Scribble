#ifndef _INSTRUCTION_LIST_DEF_H_
#define _INSTRUCTION_LIST_DEF_H_
#include <Pointers/SmartPointer.hpp>
#include <stdio.h>

class InstructionList {
private:
	SP<unsigned char> bytecode_;
	size_t length_;

public:
	InstructionList(SP<unsigned char> bytecode, size_t length);
	~InstructionList();

	unsigned char getChar(size_t position) {
		return bytecode_.Get()[position];
	}

	int getInt(size_t position) {
		unsigned char* cur = bytecode_.Get();
		cur += position;
		return *((int*)cur);
	}

	size_t length() {
		return length_;
	}
};

#endif //_INSTRUCTION_LIST_DEF_H_