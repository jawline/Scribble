/*
 * Float32.hpp
 *
 *  Created on: 16 Nov 2013
 *      Author: blake
 */

#ifndef FLOAT32_HPP_
#define FLOAT32_HPP_
#include "Value.hpp"
#include <types.h>

class Float32Value: public Value {
private:
	float32_t value_;

public:
	Float32Value(float32_t value);
	virtual ~Float32Value();

	float32_t getValue() {
		return value_;
	}

	void setValue(float32_t v) {
		value_ = v;
	}

	Type* type();
	Value* clone();
	void applyOperator(ValueOperator v, Value* r);
};

#endif /* FLOAT32_HPP_ */
