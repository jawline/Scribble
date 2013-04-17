/*
 * IfStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "IfStatement.hpp"
#include <Value/Bool.hpp>
#include <Value/Void.hpp>
#include <Statement/Heap.hpp>
#include <Statement/ReturnStatement.hpp>

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
	bool val = v->value();
	valueHeap.free(v);

	if (val) {

		for (unsigned int i = 0; i < ifTrueStatements_.size(); ++i) {
			valueHeap.free(ifTrueStatements_[i]->execute(variables));
		}

	} else {

		for (unsigned int i = 0; i < ifFalseStatements_.size(); i++) {
			valueHeap.free(ifFalseStatements_[i]->execute(variables));
		}

	}

	return valueHeap.make(Void);
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
