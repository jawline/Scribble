/*
 * Float32.cpp
 *
 *  Created on: 16 Nov 2013
 *      Author: blake
 */

#include "Float32.hpp"
#include "TypeManager.hpp"
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Statement/StatementException.hpp>

Float32Value::Float32Value(float32_t value) : value_(value) {
	// TODO Auto-generated constructor stub

}

Float32Value::~Float32Value() {
	// TODO Auto-generated destructor stub
}



void Float32Value::applyOperator(ValueOperator v, Value* r) {

	Float32Value* other = (Float32Value*) r;

	switch (v) {

	case Assign:
		value_ = other->getValue();
		break;

	default:
		throw StatementException(0,
				"Operation not value on Float32");
		break;
	}

}

Value* Float32Value::clone() {
	return valueHeap.make(value_);
}

Type* Float32Value::type() {
	return getFloat32Type();
}
