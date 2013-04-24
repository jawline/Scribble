/*
 * Bool.hpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#ifndef BOOL_HPP_
#define BOOL_HPP_
#include "Value.hpp"
#include <Statement/Heap.hpp>

class BoolValue: public Value {
private:
	bool value_;

public:
	BoolValue(bool value);
	virtual ~BoolValue();

	bool value();

	void setValue(bool v);

	Type* type();

	Value* clone();

	void applyOperator(ValueOperator v, Value* r);
};

#endif /* BOOL_HPP_ */
