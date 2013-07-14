/*
 * WhileStatement.cpp
 *
 *  Created on: 18 Mar 2013
 *      Author: blake
 */

#include "WhileStatement.hpp"
#include <Value/Void.hpp>
#include <Value/Bool.hpp>
#include <Value/TypeManager.hpp>
#include <sstream>

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

Value* WhileStatement::execute(std::vector<Value*> const& variables) {

	BoolValue* conditionResult = 0;

	while ((conditionResult = ((BoolValue*) condition_->execute(variables)))->value()
			== true) {
		valueHeap.free(conditionResult);

		for (unsigned int i = 0; i < statements_.size(); ++i) {
			valueHeap.free(statements_[i]->execute(variables));
		}

	}

	valueHeap.free(conditionResult);
	return valueHeap.make(getVoidType());
}

Type* WhileStatement::type() {
	return getTypeManager().getType(Void);
}

int WhileStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	std::stringstream body;
	int numInstr = 0;

	body << "#while body\n";

	for (unsigned int i = 0; i < statements_.size(); i++) {
		numInstr += statements_[i]->generateCode(-1, body);
	}

	int numBodyInstructions = numInstr;

	generated << "#while conditions\n";
	numInstr += condition_->generateCode(5, generated);

	generated << "#while test condition result\n";
	generated << "eq $5 0\n";
	generated << "jmpr " << numBodyInstructions+2 << "\n";

	numInstr += 2;

	generated << body.str();

	generated << "#return to sender\n";
	generated << "jmpr -" << (numInstr + 1) << "\n";

	numInstr++;

	return numInstr;
}
