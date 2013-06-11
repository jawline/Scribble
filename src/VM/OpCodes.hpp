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
	OpLoadRegister = 0,
	OpMoveRegister,
	OpJumpRegister,
	OpPushIntRegister,
	OpPushLongRegister,
	OpPopIntRegister,
	OpPopLongRegister,
	OpAddLong,
	OpTestEqual,
	OpTestNotEqual,
	OpTestLongEqual,
	OpTestLongNotEqual
};

}

#endif /* OPCODES_HPP_ */
