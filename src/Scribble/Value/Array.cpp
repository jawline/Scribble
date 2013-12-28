/*
 * Array.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#include "Array.hpp"
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Statement/StatementException.hpp>

ArrayValue::ArrayValue(Type* type) :
		type_(type), data_(nullptr) {
	length_ = 0;
}

ArrayValue::~ArrayValue() {
	// TODO Auto-generated destructor stub
}

Type* ArrayValue::type() {
	return type_;
}

Value* ArrayValue::clone() {
	ArrayValue* r = (ArrayValue*) valueHeap.make(type());
	r->setArrayData(getArrayData(), getStart(), getLength());
	return r;
}

void ArrayValue::applyOperator(ValueOperator v, Value* r) {

	if (v == Assign) {
		ArrayValue* other = (ArrayValue*) r;
		setArrayData(other->getArrayData(), other->getStart(),
				other->getLength());
		return;
	}

	throw StatementException(nullptr, "Invalid operator");
}

void ArrayValue::setArrayData(SmartPointer<ArrayData> d, int start, int length) {
	data_ = d;
	start_ = start;
	length_ = length;
}

int ArrayValue::getStart() {
	return start_;
}

int ArrayValue::getLength() {
	return length_;
}
