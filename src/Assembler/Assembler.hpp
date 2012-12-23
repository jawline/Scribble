#ifndef _ASSEMBLER_DEF_H_
#define _ASSEMBLER_DEF_H_

class Assembler {
private:
	unsigned int current_;
	unsigned int currentLine_;
	unsigned int currentInstruction_;

public:

	unsigned char* generateBytecode(unsigned char* code);

};

#endif //_ASSEMBLER_DEF_H_
