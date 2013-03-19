/*
 * ForStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "ForStatement.hpp"
#include <Value/Bool.hpp>
#include <Value/Void.hpp>

ForStatement::ForStatement(int lineNo, std::string sym, SafeStatement initial,
		SafeStatement condition, SafeStatement step,
		std::vector<SafeStatement> statements) :
		Statement(lineNo, sym) {
	initial_ = initial;
	condition_ = condition;
	step_ = step;
	statements_ = statements;

}

ForStatement::~ForStatement() {
	// TODO Auto-generated destructor stub
}

Value* ForStatement::execute(std::vector<Value*> const& variables) {

	delete initial_->execute(variables);

	BoolValue* condition;
	while ((condition = ((BoolValue*) condition_->execute(variables)))->value()) {
		delete condition;

		for (unsigned int i = 0; i < statements_.size(); ++i) {
			delete statements_[i]->execute(variables);
		}

		delete step_->execute(variables);
	}

	delete condition;

	return new VoidValue();
}

ValueType ForStatement::type() {
	return Void;
}

void ForStatement::checkTree(ValueType functionType) {
	initial_->checkTree(functionType);
	condition_->checkTree(functionType);
	step_->checkTree(functionType);

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->checkTree(functionType);
	}

	if (condition_->type() != Boolean) {
		throw StatementException(this,
				"For second paramater must evaluate to a boolean");
	}
}
