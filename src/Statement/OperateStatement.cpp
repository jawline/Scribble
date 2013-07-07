/*
 * AddStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "OperateStatement.hpp"
#include <Statement/Heap.hpp>
#include <Value/TypeManager.hpp>

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
}

int OperateStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int instrs = lhs_->generateCode(3, generated);
	instrs += rhs_->generateCode(4, generated);

	switch (op_) {

	case Assign: {
		printf("UNIMPLEMENTED ARGH\n");
		break;
	}

	case Add: {
		generated << "add $3 $4 $5\n";
		instrs += 1;

		generated << "move $5 $" << resultRegister << "\n";
		instrs += 1;
		break;
	}

	}

	return instrs;
}
