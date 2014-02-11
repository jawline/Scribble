/*
 * AndStatement.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: blake
 */

#include "AndStatement.hpp"
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Value/Bool.hpp>
#include <VM/Constants.hpp>
#include <sstream>

AndStatement::AndStatement(int lineNo, std::string sym,
		SafeStatement leftHandSide, SafeStatement rightHandSide) :
		Statement(lineNo, sym), lhs_(leftHandSide), rhs_(rightHandSide) {
	// TODO Auto-generated constructor stub

}

AndStatement::~AndStatement() {
	// TODO Auto-generated destructor stub
}

void AndStatement::checkTree(Type* functionType) {
	lhs_->checkTree(functionType);
	rhs_->checkTree(functionType);

	if (!lhs_->type()->Equals(getTypeManager().getType(Boolean)) || !rhs_->type()->Equals(getTypeManager().getType(Boolean))) {
		throw StatementException(this, std::string("And on types ") + lhs_->type()->getTypeName() + " and " + rhs_->type()->getTypeName() + " is not possible. And can only be performed on two booleans");
	}

}

Type* AndStatement::type() {
	return getTypeManager().getType(Boolean);
}

int AndStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	if (resultRegister == -1) {
		resultRegister = VM::vmTempRegisterOne;
	}

	int instrs = 0;

	generated << "#And test\n";

	std::stringstream firstStatement;
	int firstInstrs = lhs_->generateCode(resultRegister, firstStatement);

	std::stringstream secondStatement;
	int secondInstrs = rhs_->generateCode(resultRegister, secondStatement);

	generated << firstStatement.str();
	instrs += firstInstrs;

	generated << "eqz $" << resultRegister << "\n";
	instrs++;

	generated << "jmpr " << 1 + secondInstrs << "\n";
	instrs++;

	generated << secondStatement.str();
	instrs += secondInstrs;

	//TODO: Needs to be verified

	generated << "#End of and test\n";

	return instrs;
}
