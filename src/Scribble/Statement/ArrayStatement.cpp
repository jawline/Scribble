/*
 * ArrayStatement.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 *
 */

#include "ArrayStatement.hpp"
#include <VM/Constants.hpp>
#include <Scribble/Value/Util.hpp>

namespace ScribbleCore {

ArrayStatement::ArrayStatement(int line, std::string text, TypeReference type,
		SafeStatement length) :
		Statement(line, text), type_(type), length_(length) {
}

ArrayStatement::~ArrayStatement() {
}

TypeReference ArrayStatement::type() {
	return type_;
}

void ArrayStatement::checkTree(Type* functionType) {
	length_->checkTree(functionType);

	if (length_->type()->type()->getType() != Int) {
		throw new StatementException(this,
				std::string("Type ") + length_->type()->type()->getTypeName()
						+ " cannot be used as the length of an array. Integer values must be used for array size.");
	}
}

int ArrayStatement::generateCode(int resultRegister,
		std::stringstream& generated) {
	int instrs = length_->generateCode(VM::vmTempRegisterOne, generated);
	generated << "newarray \"" << type_->type()->getTypeName() << "\" $"
			<< VM::vmTempRegisterOne << " $" << resultRegister << "\n";
	return instrs + 1;
}

}
