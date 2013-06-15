/*
 * OpCodes.hpp
 *
 *  Created on: 28 May 2013
 *      Author: blake
 */

#ifndef OPCODES_HPP_
#define OPCODES_HPP_

namespace VM {

enum OpCodes {
	OpLoadConstant = 0,
	OpMove,
	OpJump,
	OpReturn,
	OpAdd,
	OpTestEqual,
	OpTestNotEqual,
};

}

#endif /* OPCODES_HPP_ */
