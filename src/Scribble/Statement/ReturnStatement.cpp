/*
 * ReturnStatement.cpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#include "ReturnStatement.hpp"
#include <VM/Constants.hpp>

namespace ScribbleCore {

ReturnStatement::ReturnStatement(int lineNo, std::string sym, SafeStatement stm) :
		Statement(lineNo, sym) {
	stm_ = stm;
}

ReturnStatement::~ReturnStatement() {
}

void ReturnStatement::checkTree(Type* functionType) {

	if (stm_.get() == nullptr) {

		StatementAssert(this, functionType->Equals(getVoidType()),
				std::string("this function requires a return argument of type ")
						+ functionType->getTypeName());
	} else {

		stm_->checkTree(functionType);

		//TODO: Verify that this doesn't allow return nil on void functions
		/**
		 * Example:
		 * func main() { return nil; } should be invalid
		 */
		StatementAssert(this,
				functionType->Equals(stm_->type()->type())
						|| (!functionType->Equals(getVoidType())
								&& stm_->type()->type()->Equals(getNilType())),
				std::string("cannot return ")
						+ stm_->type()->type()->getTypeName()
						+ " expression. This function returns a "
						+ functionType->getTypeName());
	}
}

int ReturnStatement::generateCode(int resultRegister,
		std::stringstream& generated) {
	int num = 0;

	if (stm_ != nullptr) {
		num += stm_->generateCode(VM::vmReturnResultRegister, generated);
	}

	generated << "ret\n";
	num++;

	return num;
}

}
