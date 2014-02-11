/*
 * ArrayStatement.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 *
 */

#include "ArrayStatement.hpp"
#include "Heap.hpp"
#include <VM/Constants.hpp>
#include <Scribble/Value/Array.hpp>
#include <Scribble/Value/Util.hpp>
#include <Scribble/Value/Int.hpp>

ArrayStatement::ArrayStatement(int line, std::string text, Type* type,
		SafeStatement length) :
		Statement(line, text), type_(type), length_(length) {
}

ArrayStatement::~ArrayStatement() {
	// TODO Auto-generated destructor stub
}

Type* ArrayStatement::type() {
	return type_;
}

void ArrayStatement::checkTree(Type* functionType) {
	length_->checkTree(functionType);

	if (length_->type()->getType() != Int) {
		throw new StatementException(this, std::string("Type ") + length_->type()->getTypeName() + " cannot be used as the length of an array. Integer values must be used for array size.");
	}
}

int ArrayStatement::generateCode(int resultRegister, std::stringstream& generated) {
	int instrs = length_->generateCode(VM::vmTempRegisterOne, generated);
	generated << "newarray \"" << type_->getTypeName() << "\" $" << VM::vmTempRegisterOne << " $" << resultRegister << "\n";
	return instrs + 1;
}
