/*
 * AddStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "OperateStatement.hpp"
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

OperateStatement::OperateStatement(int lineNo, std::string sym,
		ValueOperator op, SafeStatement lhs, SafeStatement rhs) :
		Statement(lineNo, sym) {
	op_ = op;
	lhs_ = lhs;
	rhs_ = rhs;
}

OperateStatement::~OperateStatement() {
	// TODO Auto-generated destructor stub
}

Value* OperateStatement::execute(std::vector<Value*> const& variables) {
	Value* lhR = lhs_->execute(variables);
	Value* rhR = rhs_->execute(variables);
	lhR->applyOperator(op_, rhR);
	valueHeap.free(rhR);
	return lhR;
}

Type* OperateStatement::type() {
	return lhs_->type();
}

void OperateStatement::checkTree(Type* type) {
	lhs_->checkTree(type);
	rhs_->checkTree(type);

	if (!(lhs_->type()->Equals(rhs_->type()))) {
		throw StatementException(this,
				"Cannot add variables of different types");
	}

	if (!(lhs_->type()->isPrimitive())) {
		throw StatementException(this, "Cannot perform on non primitives");
	}
}

int OperateStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int instrs = lhs_->generateCode(VM::vmTempRegisterOne, generated);

	generated << "pushr $" << VM::vmTempRegisterOne << " 1\n";
	instrs++;

	instrs += rhs_->generateCode(VM::vmTempRegisterTwo, generated);

	generated << "popr $" << VM::vmTempRegisterOne << " 1\n";
	instrs++;

	switch (op_) {

	case Assign: {
		printf("UNIMPLEMENTED ARGH\n");
		break;
	}

	case Add: {
		generated << "add $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
		instrs += 1;
		break;
	}

	case Subtract: {
		generated << "sub$" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
		instrs += 1;
		break;
	}

	case Multiply: {
		generated << "mul $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
		instrs += 1;
		break;
	}

	case Divide: {
		generated << "div $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
		instrs += 1;
		break;
	}

	}

	return instrs;
}
