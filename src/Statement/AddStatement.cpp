/*
 * AddStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "AddStatement.hpp"

AddStatement::AddStatement(int lineNo, std::string sym, SafeStatement lhs,
		SafeStatement rhs) :
		Statement(lineNo, sym) {
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

void AddStatement::checkTree(ValueType type) {
	lhs_->checkTree(type);
	rhs_->checkTree(type);

	if (lhs_->type() != rhs_->type()) {
		throw new StatementException(this, "Cannot add variables of different types");
	}
}
