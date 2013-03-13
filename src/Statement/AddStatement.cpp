/*
 * AddStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "AddStatement.hpp"

AddStatement::AddStatement(SafeStatement lhs, SafeStatement rhs) {
	lhs_ = lhs;
	rhs_ = rhs;
}

AddStatement::~AddStatement() {
	// TODO Auto-generated destructor stub
}

Value* AddStatement::execute() {
	Value* lhR = lhs_->execute();
	Value* rhR = rhs_->execute();
	lhR->applyOperator(Add, rhR);
	delete rhR;
	return lhR;
}

ValueType AddStatement::type() {
	return lhs_->type();
}
