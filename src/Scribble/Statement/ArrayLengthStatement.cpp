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

	if (exp_->type()->getType() != Array) {
		throw StatementException(this,
				std::string("Cannot get length of ")
						+ exp_->type()->getTypeName()
						+ ". Can only get the length of an array");
	}

}

Type* ArrayLengthStatement::type() {
	return getIntType();
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
