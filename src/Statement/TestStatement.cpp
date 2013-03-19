/*
 * TestStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "TestStatement.hpp"
#include <Statement/StatementException.hpp>
#include <Value/Int.hpp>
#include <Value/Bool.hpp>

TestStatement::TestStatement(int lineNo, std::string sym, TestType testType,
		Statement* leftHandSide, Statement* rightHandSide) :
		Statement(lineNo, sym) {
	tType_ = testType;
	lhs_ = leftHandSide;
	rhs_ = rightHandSide;

}

TestStatement::~TestStatement() {
}

Value* TestStatement::execute(std::vector<Value*> const& variables) {

	Value* lhRes = lhs_->execute(variables);
	Value* rhRes = rhs_->execute(variables);
	Value* result = 0;

	switch (lhRes->type()) {

	case Int: {

		IntValue* il = (IntValue*) lhRes;
		IntValue* rl = (IntValue*) rhRes;

		switch (tType_) {
		case TestEquals:

			if (il->value() == rl->value()) {
				result = new BoolValue(true);
			} else {
				result = new BoolValue(false);
			}

			break;

		case TestNotEquals:
			if (il->value() == rl->value()) {
				result = new BoolValue(false);
			} else {
				result = new BoolValue(true);
			}

			break;

		case TestLess:

			if (il->value() < rl->value()) {
				result = new BoolValue(true);
			} else {
				result = new BoolValue(false);
			}

			break;
		case TestGreater:

			if (il->value() > rl->value()) {
				result = new BoolValue(true);
			} else {
				result = new BoolValue(false);
			}

			break;
		}

		break;
	}

	default:
		throw StatementException(this, "Not implemented yet");
	}

	delete lhRes;
	delete rhRes;

	return result;
}

ValueType TestStatement::type() {
	return Boolean;
}

void TestStatement::checkTree(ValueType functionType) {
	lhs_->checkTree(functionType);
	rhs_->checkTree(functionType);

	if (lhs_->type() != rhs_->type()) {
		throw StatementException(this,
				"Left hand side type should be the same as right hand side type");
	}
}
