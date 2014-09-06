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

		//Check if it's ok for a function to return nothing
		if (!functionType->Equals(getVoidType())) {
			std::stringstream errorMsg;
			errorMsg << "this function requires a return argument of type " << functionType->getTypeName();
			throw StatementException(this, errorMsg.str());
		}

	} else {

		stm_->checkTree(functionType);

		if (!(functionType->Equals(stm_->type()->type()))) {

			if (!stm_->type()->type()->Equals(getNilType())) {

				throw StatementException(this,
						std::string("cannot return ")
								+ stm_->type()->type()->getTypeName() + " expression. This function returns a "
								+ functionType->getTypeName());

			}
		}
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
