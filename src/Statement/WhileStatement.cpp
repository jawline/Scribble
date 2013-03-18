/*
 * WhileStatement.cpp
 *
 *  Created on: 18 Mar 2013
 *      Author: blake
 */

#include "WhileStatement.hpp"
#include <Value/Void.hpp>
#include <Value/Bool.hpp>

WhileStatement::WhileStatement(int lineNo, std::string sym,
		SafeStatement condition, std::vector<SafeStatement> statements) :
		Statement(lineNo, sym), condition_(condition), statements_(statements) {
}

WhileStatement::~WhileStatement() {
}

void WhileStatement::checkTree(ValueType functionType) {

	condition_->checkTree(functionType);

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->checkTree(functionType);
	}

	if (condition_->type() != Boolean) {
		throw StatementException(this,
				"While condition must evaluate to a boolean");
	}
}

Value* WhileStatement::execute() {

	BoolValue* conditionResult = 0;

	while ((conditionResult = ((BoolValue*) condition_->execute()))->value()
			== true) {

		delete conditionResult;

		for (unsigned int i = 0; i < statements_.size(); ++i) {
			delete statements_[i]->execute();
		}

	}

	delete conditionResult;

	return new VoidValue();
}

ValueType WhileStatement::type() {
	return Void;
}
