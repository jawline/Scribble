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

extern VM::VMNamespace* currentNamespace;

using namespace SimpleASM;
using namespace VM;

VMNamespace Parser::parse(std::string const& text) {

    sasm__scan_string(text.c_str());
    sasm_parse();

    VMNamespace copy = *currentNamespace;
    delete currentNamespace;
    return copy;
}