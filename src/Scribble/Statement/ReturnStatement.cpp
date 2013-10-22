/*
 * ReturnStatement.cpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#include "ReturnStatement.hpp"
#include "Heap.hpp"
#include <VM/Constants.hpp>

ReturnStatement::ReturnStatement(int lineNo, std::string sym, SafeStatement stm) :
		Statement(lineNo, sym) {
	stm_ = stm;
}

ReturnStatement::~ReturnStatement() {
	// TODO Auto-generated destructor stub
}

void ReturnStatement::checkTree(Type* functionType) {

	if (stm_.get() == nullptr) {

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

	if (stm_.get() == nullptr) {
		Return j(valueHeap.make(getVoidType()));
		throw j;
	} else {
		Return r(stm_->execute(variables));
		throw r;
	}
}

int ReturnStatement::generateCode(int resultRegister, std::stringstream& generated) {
	int num = stm_->generateCode(VM::vmReturnResultRegister, generated);
	generated << "ret\n";
	return 1 + num;
}
