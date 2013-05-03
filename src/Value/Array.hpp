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
#include <stdio.h>

class ArrayValue: public Value {
private:
	int start_;
	int length_;
	Type* type_;
	SmartPointer<ArrayData> data_;

public:
	ArrayValue(Type* type);
	virtual ~ArrayValue();

	Type* type();
	Value* clone();

	void applyOperator(ValueOperator v, Value* r);

	SP<ArrayData> getArrayData() {
		return data_;
	}

	int getStart();
	int getLength();
	void setArrayData(SP<ArrayData> d, int start, int l);
};

#endif /* ARRAY_SYS_HPP_ */
