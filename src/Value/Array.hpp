/*
 * Array.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef ARRAY_SYS_HPP_
#define ARRAY_SYS_HPP_
#include "Value.hpp"
#include "ArrayData.hpp"

class ArrayValue : public Value {
private:
	Type* type_;SP<ArrayData> data_;

public:
	ArrayValue(Type* type);
	virtual ~ArrayValue();

	Type* type();
	Value* clone();
	void applyOperator(ValueOperator v, Value* r);
};

#endif /* ARRAY_SYS_HPP_ */
