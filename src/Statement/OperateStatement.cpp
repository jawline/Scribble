/*
 * AddStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "OperateStatement.hpp"

OperateStatement::OperateStatement(int lineNo, std::string sym, ValueOperator op, SafeStatement lhs,
		SafeStatement rhs) :
		Statement(lineNo, sym) {
	op_ = op;
	lhs_ = lhs;
	rhs_ = rhs;
}

OperateStatement::~OperateStatement() {
	// TODO Auto-generated destructor stub
}

Value* OperateStatement::execute() {
	Value* lhR = lhs_->execute();
	Value* rhR = rhs_->execute();
	lhR->applyOperator(op_, rhR);
	delete rhR;
	return lhR;
}

ValueType OperateStatement::type() {
	return lhs_->type();
}

void OperateStatement::checkTree(ValueType type) {
	lhs_->checkTree(type);
	rhs_->checkTree(type);

	if (lhs_->type() != rhs_->type()) {
		throw new StatementException(this, "Cannot add variables of different types");
	}
}
