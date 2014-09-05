/*
 * NotStatement.cpp
 *
 *  Created on: 5 Sep 2014
 *      Author: blake
 */

#include "NotStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

NotStatement::NotStatement(int lineno, std::string symb, SafeStatement exp) :
		Statement(lineno, symb), exp_(exp) {
}

NotStatement::~NotStatement() {
}

void NotStatement::checkTree(Type* functionType) {
	exp_->checkTree(functionType);

	if (!exp_->type()->type->Equals(getTypeManager().getType(Boolean))) {

		throw StatementException(this,
				"A not expression (!expr) can only be used on a boolean value");

	}
}

TypeReference NotStatement::type() {
	return makeTypeReference(getTypeManager().getType(Boolean));
}

int NotStatement::generateCode(int resultRegister,
		std::stringstream& generated) {
	int instrs = 0;

	instrs += exp_->generateCode(resultRegister, generated);

	if (resultRegister != -1) {
		generated << "not $" << resultRegister << "\n";
		instrs++;
	}

	return instrs;
}

} /* namespace ScribbleCore */
