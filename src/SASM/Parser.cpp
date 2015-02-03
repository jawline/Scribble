/*
 * Parser.cpp
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

extern VM::VMNamespace CurrentNamespace;

namespace SimpleASM {

VM::VMNamespace Parser::parse(std::string const& text) {

    //Parse the actual code
    sasm__scan_string(text.c_str());
    sasm_parse();

    VM::VMNamespace current = CurrentNamespace;
    CurrentNamespace = VM::VMNamespace();

    //Copy the parsed instructions into an instruction set
    return current;
}

} /* namespace SimpleASM */
