/*
 * BoolStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "BoolStatement.hpp"
#include <Value/Bool.hpp>

BoolStatement::BoolStatement(int lineNo, std::string sym, bool value) : Statement(lineNo, sym) {
	value_ = value;
}

BoolStatement::~BoolStatement() {
}

Value* BoolStatement::execute(std::vector<Value*> const& variables) {
	return new BoolValue(value_);
}

ValueType BoolStatement::type() {
	return Boolean;
}

void BoolStatement::checkTree(ValueType functionType) {
}
