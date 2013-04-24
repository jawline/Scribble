/*
 * ForStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "ForStatement.hpp"
#include <Value/Bool.hpp>
#include <Value/Void.hpp>
#include <Statement/Heap.hpp>
#include <Value/TypeManager.hpp>

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

	valueHeap.free(initial_->execute(variables));

	BoolValue* condition;
	while ((condition = ((BoolValue*) condition_->execute(variables)))->value()) {
		valueHeap.free(condition);

		for (unsigned int i = 0; i < statements_.size(); ++i) {
			valueHeap.free(statements_[i]->execute(variables));
		}

		valueHeap.free(step_->execute(variables));
	}

	valueHeap.free(condition);

	return valueHeap.make(getVoidType());
}

Type* ForStatement::type() {
	return getTypeManager().getType(Void);
}

void ForStatement::checkTree(Type* functionType) {
	initial_->checkTree(functionType);
	condition_->checkTree(functionType);
	step_->checkTree(functionType);

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->checkTree(functionType);
	}

	if (condition_->type()->getType() != Boolean) {
		throw StatementException(this,
				"For second paramater must evaluate to a boolean");
	}
}
