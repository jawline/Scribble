/*
 * IncrementStatement.cpp
 *
 *  Created on: 27 Mar 2013
 *      Author: blake
 */

#include "IncrementStatement.hpp"
#include <Value/Int.hpp>

IncrementStatement::IncrementStatement(int line, std::string sym,
		SP<Variable> variable, IncrementType op, bool post) :
		Statement(line, sym), variable_(variable), operator_(op), post_(post) {
	oneVal_ = new IntValue(1);
}

IncrementStatement::~IncrementStatement() {
}

void IncrementStatement::checkTree(ValueType functionType) {

	if (variable_->getType() != Int) {
		throw StatementException(this,
				"Increment invalid on types other than int");
	}

}

Value* IncrementStatement::execute(std::vector<Value*> const& variables) {

	switch (operator_) {

	case Increment: {
		Value* result = 0;

		if (post_) {
			variables[variable_->getPosition()]->applyOperator(Add, oneVal_);
			result = variables[variable_->getPosition()]->clone();
		} else {
			result = variables[variable_->getPosition()]->clone();
			variables[variable_->getPosition()]->applyOperator(Add, oneVal_);
		}

		return result;
	}

	case Decrement: {
		Value* result = 0;

		if (post_) {
			variables[variable_->getPosition()]->applyOperator(Subtract,
					oneVal_);
			result = variables[variable_->getPosition()]->clone();
		} else {
			result = variables[variable_->getPosition()]->clone();
			variables[variable_->getPosition()]->applyOperator(Subtract,
					oneVal_);
		}

		return result;
	}

	default:
		throw StatementException(this, "Not a valid increment operator");
		break;

	}

	return 0;
}

ValueType IncrementStatement::type() {
	return Int;
}
