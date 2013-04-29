/*
 * AndStatement.cpp
 *
 *  Created on: 27 Apr 2013
 *      Author: blake
 */

#include "AndStatement.hpp"
#include <Value/TypeManager.hpp>
#include <Statement/Heap.hpp>
#include <Value/Bool.hpp>

AndStatement::AndStatement(int lineNo, std::string sym,
		SafeStatement leftHandSide, SafeStatement rightHandSide) :
		Statement(lineNo, sym), lhs_(leftHandSide), rhs_(rightHandSide) {

}

AndStatement::~AndStatement() {
}

Value* AndStatement::execute(std::vector<Value*> const& variables) {
	BoolValue* lhs = (BoolValue*) lhs_->execute(variables);
	BoolValue* rhs = (BoolValue*) rhs_->execute(variables);

	bool result = lhs->value() & rhs->value();

	valueHeap.free(lhs);
	valueHeap.free(rhs);

	return valueHeap.make(result);
}

Type* AndStatement::type() {
	return getBooleanType();
}

void AndStatement::checkTree(Type* functionType) {
	lhs_->checkTree(functionType);
	rhs_->checkTree(functionType);

	if (lhs_->type() == getBooleanType() && rhs_->type() == getBooleanType()) {

	} else {
		throw StatementException(this,
				"Expecting LHS and RHS to both be booleans at &");
	}

}
