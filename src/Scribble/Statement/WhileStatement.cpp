/*
 * WhileStatement.cpp
 *
 *  Created on: 18 Mar 2013
 *      Author: blake
 */

#include "WhileStatement.hpp"
#include <sstream>
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

namespace ScribbleCore {

WhileStatement::WhileStatement(int lineNo, std::string sym,
		SafeStatement condition, std::vector<SafeStatement> statements) :
		Statement(lineNo, sym), condition_(condition), statements_(statements) {
}

WhileStatement::~WhileStatement() {
}

void WhileStatement::checkTree(Type* functionType) {

	condition_->checkTree(functionType);

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->checkTree(functionType);
	}

	if (condition_->type()->getType() != Boolean) {
		throw StatementException(this,
				"While condition must evaluate to a boolean");
	}
}

Type* WhileStatement::type() {
	return getTypeManager().getType(NilType);
}

int WhileStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	std::stringstream body;
	int numInstr = 0;
	int numBodyInstrs = 0;

	body << "--while body\n";

	for (unsigned int i = 0; i < statements_.size(); i++) {
		numBodyInstrs += statements_[i]->generateCode(-1, body);
	}


	generated << "--while conditions\n";
	numInstr += condition_->generateCode(VM::vmTempRegisterThree, generated);

	generated << "--while test condition result\n";

	generated << "eq $" << VM::vmTempRegisterThree << " 0\n";
	numInstr += 2;

	generated << "jmpr " << numBodyInstrs + 2 << "\n";
	numInstr += 1;

	generated << body.str();
	numInstr += numBodyInstrs;

	generated << "--return to sender\n";
	generated << "jmpr -" << (numInstr) << "\n";

	numInstr++;

	return numInstr;
}

}
