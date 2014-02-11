/*
 * ArrayLengthStatement.cpp
 *
 *  Created on: 29 Apr 2013
 *      Author: blake
 */

#include "ArrayLengthStatement.hpp"
#include "Heap.hpp"
#include <Scribble/Value/Array.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

ArrayLengthStatement::ArrayLengthStatement(int line, std::string text,
		SafeStatement exp) :
		Statement(line, text), exp_(exp) {

}

ArrayLengthStatement::~ArrayLengthStatement() {

}

void ArrayLengthStatement::checkTree(Type* functionType) {
	exp_->checkTree(functionType);

	if (exp_->type()->getType() != Array) {
		throw StatementException(this, std::string("Cannot get length of ") + exp_->type()->getTypeName() + ". Can only get the length of an array");
	}

}

Type* ArrayLengthStatement::type() {
	return getIntType();
}

int ArrayLengthStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	if (resultRegister != -1) {

		int numArr = exp_->generateCode(VM::vmTempRegisterOne, generated);

		generated << "alen $" << VM::vmTempRegisterOne << " $" << resultRegister
				<< "\n";

		return numArr + 1;
	}

	return 0;
}
