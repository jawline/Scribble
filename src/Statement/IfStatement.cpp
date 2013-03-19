/*
 * IfStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "IfStatement.hpp"
#include <Value/Bool.hpp>
#include <Value/Void.hpp>

IfStatement::IfStatement(int lineNo, std::string sym, SP<Statement> condition,
		std::vector<SP<Statement>> ifTrueStatements,
		std::vector<SP<Statement>> ifFalseStatements) :
		Statement(lineNo, sym) {
	condition_ = condition;
	ifTrueStatements_ = ifTrueStatements;
	ifFalseStatements_ = ifFalseStatements;
}

IfStatement::~IfStatement() {
}

Value* IfStatement::execute(std::vector<Value*> const& variables) {

	BoolValue* v = (BoolValue*) condition_->execute(variables);

	if (v->value()) {

		for (unsigned int i = 0; i < ifTrueStatements_.size(); ++i) {
			delete ifTrueStatements_[i]->execute(variables);
		}

	} else {

		for (unsigned int i = 0; i < ifFalseStatements_.size(); i++) {
			delete ifFalseStatements_[i]->execute(variables);
		}

	}

	delete v;

	return new VoidValue();
}

void IfStatement::checkTree(ValueType functionType) {
	condition_->checkTree(functionType);

	if (condition_->type() != Boolean) {
		throw StatementException(this, "If statement needs boolean condition");
	}

	for (unsigned int i = 0; i < ifTrueStatements_.size(); ++i) {
		ifTrueStatements_[i]->checkTree(functionType);
	}

	for (unsigned int i = 0; i < ifFalseStatements_.size(); ++i) {
		ifFalseStatements_[i]->checkTree(functionType);
	}
}
