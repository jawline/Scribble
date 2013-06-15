/*
 * SAsm.cpp
 *
 *  Created on: 11 Jun 2013
 *      Author: blake
 */

#include "Parser.hpp"
#include <stdint.h>
#include <string>
#include <algorithm>    // std::find_if
extern void sasm_parse();
extern void sasm__scan_string(char const*);
extern void sasm_lex_destroy();


extern uint8_t* buffer;
extern int current;

extern uint8_t* constant;
extern int currentConstant;

namespace SimpleASM {

VM::InstructionSet Parser::parse(std::string text) {

	sasm__scan_string(text.c_str());
	sasm_parse();

	return VM::InstructionSet(buffer, current, constant, currentConstant, 0);
}

} /* namespace SimpleASM */
