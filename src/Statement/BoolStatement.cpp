/*
 * BoolStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "BoolStatement.hpp"
#include <Value/Bool.hpp>
#include <Statement/Heap.hpp>

BoolStatement::BoolStatement(int lineNo, std::string sym, bool value) : Statement(lineNo, sym) {
	value_ = value;
}

BoolStatement::~BoolStatement() {
}

Value* BoolStatement::execute(std::vector<Value*> const& variables) {
	BoolValue* gen = (BoolValue*) valueHeap.make(Boolean);
	gen->setValue(value_);
	return gen;
}

ValueType BoolStatement::type() {
	return Boolean;
}

void BoolStatement::checkTree(ValueType functionType) {
}
