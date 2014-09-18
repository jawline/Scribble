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

	StatementAssert(this, condition_->type()->type()->getType() == Boolean,
			"The while condition expression (while * do) must be a boolean value");
}

TypeReference WhileStatement::type() {
	return makeTypeReference(getTypeManager().getType(Void));
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
