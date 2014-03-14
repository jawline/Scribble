/*
 * OrStatement.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: blake
 */

#include "OrStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>
#include <sstream>

namespace ScribbleCore {

OrStatement::OrStatement(int lineNo, std::string sym,
		SafeStatement leftHandSide, SafeStatement rightHandSide) :
		Statement(lineNo, sym), lhs_(leftHandSide), rhs_(rightHandSide) {

}

OrStatement::~OrStatement() {
	// TODO Auto-generated destructor stub
}

void OrStatement::checkTree(Type* functionType) {

	lhs_->checkTree(functionType);
	rhs_->checkTree(functionType);

	if (!lhs_->type()->Equals(getTypeManager().getType(Boolean))) {
		throw StatementException(this, "And can only be performed on booleans");
	}

	if (!rhs_->type()->Equals(getTypeManager().getType(Boolean))) {
		throw StatementException(this, "And can only be performed on booleans");
	}

}

Type* OrStatement::type() {
	return getTypeManager().getType(Boolean);
}

int OrStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	if (resultRegister == -1) {
		resultRegister = VM::vmTempRegisterOne;
	}

	int instrs = 0;

	generated << "--Or test\n";

	std::stringstream firstStatement;
	int firstInstrs = lhs_->generateCode(resultRegister, firstStatement);

	std::stringstream secondStatement;
	int secondInstrs = rhs_->generateCode(resultRegister, secondStatement);

	generated << firstStatement.str();
	instrs += firstInstrs;

	generated << "eqz $" << resultRegister << "\n";
	instrs++;

	generated << "jmpr 2\n";
	instrs++;

	generated << "jmpr " << 1 + secondInstrs << "\n";
	instrs++;

	generated << secondStatement.str();
	instrs += secondInstrs;

	//TODO: Needs to be verified

	generated << "--End of or test\n";

	return instrs;
}

}
