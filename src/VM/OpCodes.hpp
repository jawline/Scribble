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
		NoOp = 0,
		OpAdd,
		OpSub,
		OpMul,
		OpDiv,
		OpJump,
		OpPush,
		OpPop
	};

};


#endif /* OPCODES_HPP_ */
