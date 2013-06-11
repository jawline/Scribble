/*
 * SAsm.hpp
 *
 *  Created on: 11 Jun 2013
 *      Author: blake
 */

#ifndef SASM_HPP_
#define SASM_HPP_
#include "InstructionSet.hpp"
#include <string>

namespace SimpleASM {

class SAsm {
public:
	SAsm();
	virtual ~SAsm();

	static VM::InstructionSet parse(std::string text);
};

} /* namespace SimpleASM */
#endif /* SASM_HPP_ */
