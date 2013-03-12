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

TestStatement::TestStatement(TestType testType, Statement* leftHandSide,
		Statement* rightHandSide) {
	tType_ = testType;
	lhs_ = leftHandSide;
	rhs_ = rightHandSide;

}

TestStatement::~TestStatement() {
}

Value* TestStatement::execute() {

	Value* lhRes = lhs_->execute();
	Value* rhRes = rhs_->execute();
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
		throw StatementException("Not implemented yet");
	}

	delete lhRes;
	delete rhRes;

	return result;
}

ValueType TestStatement::type() {
	return Boolean;
}
