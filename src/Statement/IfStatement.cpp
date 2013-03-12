/*
 * IfStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "IfStatement.hpp"
#include <Value/Bool.hpp>

IfStatement::IfStatement(SP<Statement> condition,
		std::vector<SP<Statement>> ifTrueStatements,
		std::vector<SP<Statement>> ifFalseStatements) {
	condition_ = condition;
	ifTrueStatements_ = ifTrueStatements;
	ifFalseStatements_ = ifFalseStatements;
}

IfStatement::~IfStatement() {
}

Value* IfStatement::execute() {

	BoolValue* v = (BoolValue*) condition_->execute();

	if (v->value()) {

		for (unsigned int i = 0; i < ifTrueStatements_.size(); ++i) {
			ifTrueStatements_[i]->execute();
		}

	} else {

		for (unsigned int i = 0; i < ifFalseStatements_.size(); i++) {
			ifFalseStatements_[i]->execute();
		}

	}
}
