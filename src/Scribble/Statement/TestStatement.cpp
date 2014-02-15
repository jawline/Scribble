/*
 * TestStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "TestStatement.hpp"
#include <VM/Constants.hpp>
#include <Scribble/Statement/StatementException.hpp>
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

TestStatement::TestStatement(int lineNo, std::string sym, TestType testType,
		SafeStatement leftHandSide, SafeStatement rightHandSide) :
		Statement(lineNo, sym) {
	tType_ = testType;
	lhs_ = leftHandSide;
	rhs_ = rightHandSide;

}

TestStatement::~TestStatement() {
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

}
