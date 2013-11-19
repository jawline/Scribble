/*
 * TestStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "TestStatement.hpp"
#include <VM/Constants.hpp>
#include <Scribble/Statement/StatementException.hpp>
#include <Scribble/Value/Int.hpp>
#include <Scribble/Value/Bool.hpp>
#include <Scribble/Value/String.hpp>
#include <Scribble/Value/Float32.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Value/TypeManager.hpp>

TestStatement::TestStatement(int lineNo, std::string sym, TestType testType,
		SafeStatement leftHandSide, SafeStatement rightHandSide) :
		Statement(lineNo, sym) {
	tType_ = testType;
	lhs_ = leftHandSide;
	rhs_ = rightHandSide;

}

TestStatement::~TestStatement() {
}

Value* TestStatement::execute(std::vector<Value*> const& variables) {

	Value* lhRes = lhs_->execute(variables);
	Value* result = 0;

	Value* rhRes = rhs_->execute(variables);

	switch (lhRes->type()->getType()) {

	case Boolean: {
		BoolValue* bl = (BoolValue*) lhRes;
		BoolValue* br = (BoolValue*) rhRes;

		switch (tType_) {

		case TestEquals:
			result = valueHeap.make(bl->value() == br->value());
			break;

		case TestNotEquals:
			result = valueHeap.make(bl->value() != br->value());
			break;

		default:
			throw StatementException(this,
					"Boolean cannot be tested with anything other than equality and and");
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

		case TestLessOrEqual:
			result = valueHeap.make((il->value() <= rl->value()));
			break;

		case TestGreaterOrEqual:
			result = valueHeap.make((il->value() >= rl->value()));
			break;
		}

		break;
	}

	case Float32: {

		Float32Value* il = (Float32Value*) lhRes;
		Float32Value* rl = (Float32Value*) rhRes;

		switch (tType_) {
		case TestEquals:
			//Result is a bool test of truth
			result = valueHeap.make((il->getValue() == rl->getValue()));
			break;

		case TestNotEquals:
			result = valueHeap.make(!(il->getValue() == rl->getValue()));
			break;

		case TestLess:
			result = valueHeap.make((il->getValue() < rl->getValue()));
			break;

		case TestGreater:
			result = valueHeap.make((il->getValue() > rl->getValue()));
			break;

		case TestLessOrEqual:
			result = valueHeap.make((il->getValue() <= rl->getValue()));
			break;

		case TestGreaterOrEqual:
			result = valueHeap.make((il->getValue() >= rl->getValue()));
			break;
		}

		break;
	}

	case String: {

		StringValue* sl = (StringValue*) lhRes;
		StringValue* sr = (StringValue*) rhRes;

		switch (tType_) {

		case TestEquals:
			result = valueHeap.make(
					sl->getValue().compare(sr->getValue()) == 0);
			break;

		case TestNotEquals:
			result = valueHeap.make(
					!(sl->getValue().compare(sr->getValue()) == 0));
			break;

		default:
			throw StatementException(this, "Not implemented yet");
		}

		break;
	}

	default:
		throw StatementException(this, "Type: Not implemented yet");
	}

	valueHeap.free(rhRes);
	valueHeap.free(lhRes);

	return result;
}

Type* TestStatement::type() {
	return getTypeManager().getType(Boolean);
}

void TestStatement::checkTree(Type* functionType) {
	lhs_->checkTree(functionType);
	rhs_->checkTree(functionType);

	if (!lhs_->type()->Equals(rhs_->type())) {
		throw StatementException(this,
				"Left hand side type should be the same as right hand side type");
	}

}

int TestStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int instrs = 0;

	generated << "#Test statement\n";

	instrs += lhs_->generateCode(VM::vmTempRegisterOne, generated);

	generated << "pushr $" << VM::vmTempRegisterOne << " 1\n";
	instrs += 1;

	instrs += rhs_->generateCode(VM::vmTempRegisterTwo, generated);

	generated << "popr $" << VM::vmTempRegisterOne << " 1\n";
	instrs++;

	//1
	generated << "load 0 $" << VM::vmTempRegisterThree << "\n";
	instrs++;

	switch (lhs_->type()->getType()) {

	case Boolean: {
		switch (tType_) {

		case TestEquals:
			//2
			generated << "eq $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " #test lhs rhs\n";
			instrs += 1;
			break;

		case TestNotEquals:
			generated << "neq $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << "\n";
			instrs += 1;
			break;

		default:
			throw StatementException(this, "Invalid test for type");
		}

		break;
	}

	case Float32: {

		generated << "cmpf32 $" << VM::vmTempRegisterOne << " $"
				<< VM::vmTempRegisterTwo << " $" << VM::vmTempRegisterOne
				<< "\n";
		instrs++;

		switch (tType_) {

		case TestEquals:
			generated << "eqz $" << VM::vmTempRegisterOne << "\n";
			instrs++;
			break;

		case TestNotEquals:
			generated << "eqz $" << VM::vmTempRegisterOne << "\n";
			generated << "jmpr 2\n";
			instrs += 2;
			break;

		case TestLess:
			generated << "load -1 $" << VM::vmTempRegisterTwo << "\n";
			generated << "eq $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo << "\n";
			instrs += 2;
			break;

		case TestLessOrEqual:
			generated << "load 1 $" << VM::vmTempRegisterTwo << "\n";
			generated << "lt $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo << "\n";
			instrs += 2;
			break;

		case TestGreater:
			generated << "load 1 $" << VM::vmTempRegisterTwo << "\n";
			generated << "eq $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo << "\n";
			instrs += 2;
			break;

		case TestGreaterOrEqual:
			generated << "load -1 $" << VM::vmTempRegisterTwo << "\n";
			generated << "gt $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo << "\n";
			instrs += 2;
			break;

		default:
			break;
		}

		break;
	}

	case Int: {
		switch (tType_) {

		case TestEquals:
			//2
			generated << "eq $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " #test lhs rhs\n";
			instrs += 1;
			break;

		case TestNotEquals:
			generated << "neq $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << "\n";
			instrs += 1;
			break;

		case TestLess:
			generated << "lt $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " #test less than lhs rhs\n";
			instrs += 1;
			break;

		case TestLessOrEqual:
			generated << "le $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo
					<< " #tess less or equal lhs rhs\n";
			instrs += 1;
			break;

		case TestGreater:
			generated << "gt $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " #test greater\n";
			instrs += 1;
			break;

		case TestGreaterOrEqual:
			generated << "ge $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " #test greater or equal\n";
			instrs += 1;
			break;

		default:
			printf("Test statement unimplemented.\n");
			break;
		}

		break;
	}

	default: {
		throw StatementException(this,
				"Cannot generate test code for given type");
		break;
	}

	}

	//3
	generated << "load 1 $" << VM::vmTempRegisterThree << "\n";
	instrs++;

	//Move the temp register result to the result register if they aren't the same register ( For example for will temp 3 to store its condition )
	if (VM::vmTempRegisterThree != resultRegister) {
		//4
		generated << "move $" << VM::vmTempRegisterThree << " $";
		generated << resultRegister;
		generated << "\n";

		instrs++;
	}

	generated << "#Test statement end. " << instrs << " instructions\n";

	return instrs;
}
