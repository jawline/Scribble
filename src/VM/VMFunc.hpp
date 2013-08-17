/*
 * VMFunc.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: blake
 */

#ifndef VMFUNC_HPP_
#define VMFUNC_HPP_
#include <string>
#include "InstructionSet.hpp"

namespace VM {

class VMFunc {
private:
	std::string name_;
	InstructionSet instrs_;

public:
	VMFunc() : name_("INVALID") {}
	VMFunc(std::string name, InstructionSet instrs);
	virtual ~VMFunc();

	InstructionSet& getInstructions() {
		return instrs_;
	}

	std::string getName() {
		return name_;
	}
};

} /* namespace VM */
#endif /* VMFUNC_HPP_ */
