/*
 * ArrayLengthStatement.cpp
 *
 *  Created on: 29 Apr 2013
 *      Author: blake
 */

#include "ArrayLengthStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

namespace ScribbleCore {

ArrayLengthStatement::ArrayLengthStatement(int line, std::string text,
		SafeStatement exp) :
		Statement(line, text), exp_(exp) {

}

ArrayLengthStatement::~ArrayLengthStatement() {

}

void ArrayLengthStatement::checkTree(Type* functionType) {
	exp_->checkTree(functionType);

	StatementAssert(this, exp_->type()->type()->getType() == Array,
			std::string("len does not work on ")
					+ exp_->type()->type()->getTypeName()
					+ " it can only be used on arrays");
}

TypeReference ArrayLengthStatement::type() {
	return makeTypeReference(getIntType());
}

int ArrayLengthStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	//If there is a result register then place the length of the array in the result register
	//otherwise ignore the statement.
	//This means that len(a) will only generate instruction for code when the result is going to be used.
	if (resultRegister != -1) {

		int numArr = exp_->generateCode(VM::vmTempRegisterOne, generated);

		generated << "alen $" << VM::vmTempRegisterOne << " $" << resultRegister
				<< "\n";

		return numArr + 1;
	}

	return 0;
}

}
