/*
 * BoolStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "BoolStatement.hpp"
#include <Value/Bool.hpp>

BoolStatement::BoolStatement(bool value) {
	value_ = value;
}

BoolStatement::~BoolStatement() {
}

Value* BoolStatement::execute() {
	return new BoolValue(value_);
}

ValueType BoolStatement::type() {
	return Boolean;
}
