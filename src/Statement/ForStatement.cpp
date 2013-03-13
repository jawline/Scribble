/*
 * ForStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "ForStatement.hpp"
#include <Value/Bool.hpp>

ForStatement::ForStatement(SafeStatement initial, SafeStatement condition,
		SafeStatement step, std::vector<SafeStatement> statements) {
	initial_ = initial;
	condition_ = condition;
	step_ = step;
	statements_ = statements;

}

ForStatement::~ForStatement() {
	// TODO Auto-generated destructor stub
}


Value* ForStatement::execute() {

	initial_->execute();

	while (((BoolValue*)condition_->execute())->value()) {

		for (unsigned int i = 0; i < statements_.size(); ++i) {
			statements_[i]->execute();
		}

		step_->execute();
	}

}

ValueType ForStatement::type() {
	return Void;
}
