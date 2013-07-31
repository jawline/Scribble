/*
 * ReturnStatement.cpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#include "ReturnStatement.hpp"
#include "Heap.hpp"

ReturnStatement::ReturnStatement(int lineNo, std::string sym, SafeStatement stm) :
		Statement(lineNo, sym) {
	stm_ = stm;
}

ReturnStatement::~ReturnStatement() {
	// TODO Auto-generated destructor stub
}

void ReturnStatement::checkTree(Type* functionType) {

	if (stm_.Null()) {

		if (!functionType->Equals(getVoidType())) {
			throw StatementException(this, "expected return argument");
		}

	} else {

		stm_->checkTree(functionType);

		if (!functionType->Equals(stm_->type())) {
			throw StatementException(this,
					"Return type differs from function type");
		}
	}
}

Value* ReturnStatement::execute(std::vector<Value*> const& variables) {

	if (stm_.Null()) {
		Return j(valueHeap.make(getVoidType()));
		throw j;
	} else {
		Return r(stm_->execute(variables));
		throw r;
	}
}
