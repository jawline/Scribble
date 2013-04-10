/*
 * Void.cpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#include "Void.hpp"
#include <Statement/StatementException.hpp>
#include <Statement/Heap.hpp>

VoidValue::VoidValue() {
	// TODO Auto-generated constructor stub

}

VoidValue::~VoidValue() {
	// TODO Auto-generated destructor stub
}

void VoidValue::applyOperator(ValueOperator, Value* other) {
	throw StatementException(0, "Not Supported");
}

ValueType VoidValue::type() {
	return Void;
}

Value* VoidValue::clone() {
	return valueHeap.make(Void);
}
