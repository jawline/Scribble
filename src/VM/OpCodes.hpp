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

	/**
	 * Arithmetic operations
	 */

	OpAdd,
	OpSub,
	OpMul,
	OpDiv,
	OpInc,
	OpDec,
	OpNot,

	/**
	 * Float operations
	 */

	OpAddFloat32,
	OpSubFloat32,
	OpMulFloat32,
	OpDivFloat32,
	OpCmpFloat32,

	/**
	 *  Tests
	 */

	OpEqual,
	OpNotEqual,
	OpEqualZero,
	OpLessThan,
	OpLessThanOrEqual,
	OpGreaterThan,
	OpGreaterThanOrEqual,

	/**
	 * Array operators
	 */

	OpNewArray,
	OpArraySet,
	OpArrayGet,
	OpArrayLength,

	/**
	 * Structure operators
	 */

	OpNewStruct,
	OpStructSetField,
	OpStructGetField,

	/**
	 * Function & Stack operators
	 */

	OpPushRegisters,
	OpPopNil,
	OpPopRegisters,
	OpCallFn,
	OpReturn
};

}

#endif /* OPCODES_HPP_ */
