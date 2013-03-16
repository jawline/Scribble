/*
 * Void.hpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#ifndef VOID_HPP_
#define VOID_HPP_
#include "Value.hpp"

class VoidValue: public Value {
public:
	VoidValue();
	virtual ~VoidValue();

	virtual void applyOperator(ValueOperator, Value* other);
	virtual ValueType type();
	virtual Value* clone();
};

#endif /* VOID_HPP_ */
