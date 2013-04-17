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
#include <Statement/Heap.hpp>

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

	case Boolean: {
		BoolValue* bl = (BoolValue*) lhRes;
		BoolValue* br = (BoolValue*) rhRes;

		switch (tType_) {
		case TestEquals:
			result = valueHeap.make(bl->value() == br->value());
			break;

		default:
			throw StatementException(this,
					"Boolean cannot be tested with anything other than assign");
			break;
		}

		break;
	}

	case Int: {

		IntValue* il = (IntValue*) lhRes;
		IntValue* rl = (IntValue*) rhRes;

		switch (tType_) {
		case TestEquals:
			//Result is a bool test of truth
			result = valueHeap.make((il->value() == rl->value()));
			break;

		case TestNotEquals:
			result = valueHeap.make(!(il->value() == rl->value()));
			break;

		case TestLess:
			result = valueHeap.make((il->value() < rl->value()));
			break;
		case TestGreater:
			result = valueHeap.make((il->value() > rl->value()));
			break;
		}

		break;
	}

	default:
		throw StatementException(this, "Not implemented yet");
	}

	valueHeap.free(lhRes);
	valueHeap.free(rhRes);

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
