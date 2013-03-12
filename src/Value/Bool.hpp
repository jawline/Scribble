/*
 * Bool.hpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#ifndef BOOL_HPP_
#define BOOL_HPP_
#include "Value.hpp"

class BoolValue: public Value {
private:
	bool value_;

public:
	BoolValue(bool value);
	virtual ~BoolValue();

	bool value() {
		return value_;
	}

	ValueType type() {
		return Boolean;
	}

	Value* clone() {
		return new BoolValue(value_);
	}

	void applyOperator(ValueOperator v, Value* r);
};

#endif /* BOOL_HPP_ */
