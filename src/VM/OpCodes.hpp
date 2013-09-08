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
	OpAdd,
	OpSub,
	OpMul,
	OpDiv,
	OpEqual,
	OpLessThan,
	OpLessThanOrEqual,
	OpAnd,
	OpNewArray,
	OpArraySet,
	OpArrayGet,
	OpPushRegisters,
	OpPopNil,
	OpPopRegisters,
	OpCallFn,
	OpReturn
};

}

#endif /* OPCODES_HPP_ */
