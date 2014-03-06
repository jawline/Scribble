/*
 * SAsm.cpp
 *
 *  Created on: 11 Jun 2013
 *      Author: blake
 */

#include "Parser.hpp"
#include <types.h>
#include <string>
#include <algorithm>    // std::find_if
extern void sasm_parse();
extern void sasm__scan_string(char const*);
extern void sasm_lex_destroy();


extern uint8_t* buffer;
extern int current;
extern int maxBuf;

extern uint8_t* constant;
extern int currentConstant;
extern int maxConst;

namespace SimpleASM {

VM::InstructionSet Parser::parse(std::string text) {

	//Parse the actual code
	sasm__scan_string(text.c_str());
	sasm_parse();

	//Copy the parsed instructions into an instruction set
	VM::InstructionSet generated = VM::InstructionSet(buffer, current, constant, currentConstant, 0);

	//Free all the data allocated during parsing and reset all values to 0
   //	delete[] buffer;
	buffer = 0;
   // delete[] constant;
	constant = 0;
	currentConstant = 0;
	current = 0;
	maxBuf = 0;
	maxConst = 0;

	return generated;
}

} /* namespace SimpleASM */
