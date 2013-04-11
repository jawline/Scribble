/*
 * Bool.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "Bool.hpp"
#include <Statement/StatementException.hpp>

BoolValue::BoolValue(bool value) {
	value_ = value;
}

BoolValue::~BoolValue() {
}

void BoolValue::applyOperator(ValueOperator v, Value* r) {

	BoolValue* other = (BoolValue*) r;

	switch (v) {

	case Assign:
		value_ = other->value();
		break;

	default:
		throw StatementException(0,
				"Booleans cannot have any operations other than assign.");
		break;
	}

}

Value* BoolValue::clone() {
	BoolValue* gen = (BoolValue*) valueHeap.make(Boolean);
	gen->setValue(value_);
	return gen;
}

ValueType BoolValue::type() {
	return Boolean;
}

bool BoolValue::value() {
	return value_;
}

void BoolValue::setValue(bool v) {
	value_ = v;
}
