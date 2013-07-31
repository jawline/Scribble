/*
 * AndStatement.cpp
 *
 *  Created on: 27 Apr 2013
 *      Author: blake
 */

#include "AndStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Value/Bool.hpp>

AndStatement::AndStatement(int lineNo, std::string sym,
		SafeStatement leftHandSide, SafeStatement rightHandSide) :
		Statement(lineNo, sym), lhs_(leftHandSide), rhs_(rightHandSide) {
}

AndStatement::~AndStatement() {
}

Value* AndStatement::execute(std::vector<Value*> const& variables) {
	BoolValue* lhs = (BoolValue*) lhs_->execute(variables);

	bool result = false;

	if (lhs->value()) {
		BoolValue* rhs = (BoolValue*) rhs_->execute(variables);
		result = lhs->value() && rhs->value();
		valueHeap.free(rhs);
	}

	valueHeap.free(lhs);

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
