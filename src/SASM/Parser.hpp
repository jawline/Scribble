/*
 * SAsm.hpp
 *
 *  Created on: 11 Jun 2013
 *      Author: blake
 */

#ifndef SASM_HPP_
#define SASM_HPP_
#include <VM/InstructionSet.hpp>
#include <string>

namespace SimpleASM {

class Parser {
public:

	static VM::InstructionSet parse(std::string text);
};

} /* namespace SimpleASM */
#endif /* SASM_HPP_ */
