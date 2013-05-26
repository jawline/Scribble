/*
 * Structure.cpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#include "Structure.hpp"
#include <Statement/Heap.hpp>
#include <Statement/StatementException.hpp>

Structure::Structure(Type* type) {
	type_ = type;
	data_ = nullptr;
}

Structure::~Structure() {
}

void Structure::applyOperator(ValueOperator v, Value* other) {

	if (v == Assign) {
		Structure* otherStruct = (Structure*) other;
		data_ = otherStruct->data_;
		return;
	}

	throw StatementException(nullptr, "Invalid operator");
}

Type* Structure::type() {
	return type_;
}

Value* Structure::clone() {
	Structure* gen = (Structure*) valueHeap.make(type_);
	gen->data_ = data_;
	return gen;
}
