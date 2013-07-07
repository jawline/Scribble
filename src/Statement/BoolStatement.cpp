/*
 * BoolStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "BoolStatement.hpp"
#include <Value/Bool.hpp>
#include <Statement/Heap.hpp>
#include <Value/TypeManager.hpp>

BoolStatement::BoolStatement(int lineNo, std::string sym, bool value) :
		Statement(lineNo, sym) {
	value_ = value;
}

BoolStatement::~BoolStatement() {
}

Value* BoolStatement::execute(std::vector<Value*> const& variables) {
	BoolValue* gen = (BoolValue*) valueHeap.make(getBooleanType());
	gen->setValue(value_);
	return gen;
}

Type* BoolStatement::type() {
	return getTypeManager().getType(Boolean);
}

void BoolStatement::checkTree(Type* functionType) {
}

int BoolStatement::generateCode(int resultRegister, std::stringstream& generated) {

	if (value_) {
		generated << "load 1 $" << resultRegister << "\n";
	} else {
		generated << "load 0 $" << resultRegister << "\n";
	}

	return 1;
}
