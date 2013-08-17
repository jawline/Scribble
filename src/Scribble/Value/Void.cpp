/*
 * Void.cpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#include "Void.hpp"
#include "TypeManager.hpp"
#include <Scribble/Statement/StatementException.hpp>
#include <Scribble/Statement/Heap.hpp>

VoidValue::VoidValue() {
	// TODO Auto-generated constructor stub

}

VoidValue::~VoidValue() {
	// TODO Auto-generated destructor stub
}

void VoidValue::applyOperator(ValueOperator, Value* other) {
	throw StatementException(0, "Not Supported");
}

Type* VoidValue::type() {
	return getVoidType();
}

Value* VoidValue::clone() {
	return valueHeap.make(getVoidType());
}