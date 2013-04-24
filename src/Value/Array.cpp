/*
 * Array.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#include "Array.hpp"
#include <Statement/Heap.hpp>
#include <Statement/StatementException.hpp>

ArrayValue::ArrayValue(Type* type) :
		type_(type), data_(nullptr) {
	// TODO Auto-generated constructor stub

}

ArrayValue::~ArrayValue() {
	// TODO Auto-generated destructor stub
}

Type* ArrayValue::type() {
	return type_;
}

Value* ArrayValue::clone() {
	ArrayValue* r = (ArrayValue*) valueHeap.make(type());
	r->data_ = data_;
	return r;
}

void ArrayValue::applyOperator(ValueOperator v, Value* r) {

	if (v == Assign) {

		data_ = ((ArrayValue*) r)->data_;
		return;
	}

	throw StatementException(nullptr, "Invalid operator");
}
