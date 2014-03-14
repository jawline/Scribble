/*
 * AndStatement.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: blake
 */

#include "AndStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>
#include <sstream>

namespace ScribbleCore {

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

	if (!lhs_->type()->Equals(getTypeManager().getType(Boolean))
			|| !rhs_->type()->Equals(getTypeManager().getType(Boolean))) {
		throw StatementException(this,
				std::string("And on types ") + lhs_->type()->getTypeName()
						+ " and " + rhs_->type()->getTypeName()
						+ " is not possible. And can only be performed on two booleans");
	}

}

Type* AndStatement::type() {
	return getTypeManager().getType(Boolean);
}

int AndStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	//If the result of the and statement is to be ignored then place the result in temp register 1 ( In this case the and statement should still be executed in case the functions involved had desired side
	//effects, though anything that causes this would be very badly written code )

	if (resultRegister == -1) {
		resultRegister = VM::vmTempRegisterOne;
	}

	int instrs = 0;

	generated << "--And test\n";

	std::stringstream firstStatement;
	int firstInstrs = lhs_->generateCode(resultRegister, firstStatement);

	std::stringstream secondStatement;
	int secondInstrs = rhs_->generateCode(resultRegister, secondStatement);

	//Add the first statement to the code
	generated << firstStatement.str();
	instrs += firstInstrs;

	//If the result of the first statement equals zero then jump out as the second statement doesn't need to be tested.
	generated << "eqz $" << resultRegister << "\n";
	instrs++;

	generated << "jmpr " << 1 + secondInstrs << "\n";
	instrs++;

	//Add the second statement test to the code.
	generated << secondStatement.str();
	instrs += secondInstrs;

	//TODO: Needs to be verified

	generated << "--End of and test\n";

	return instrs;
}

}
