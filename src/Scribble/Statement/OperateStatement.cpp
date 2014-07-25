/*
 * AddStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "OperateStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

namespace ScribbleCore {

OperateStatement::OperateStatement(int lineNo, std::string sym,
		ValueOperator op, SafeStatement lhs, SafeStatement rhs) :
		Statement(lineNo, sym) {
	op_ = op;
	lhs_ = lhs;
	rhs_ = rhs;
}

OperateStatement::~OperateStatement() {
}

TypeReference OperateStatement::type() {
	return lhs_->type();
}

void OperateStatement::checkTree(Type* type) {
	lhs_->checkTree(type);
	rhs_->checkTree(type);

	if (!(lhs_->type()->type->Equals(rhs_->type()->type))) {
		throw StatementException(this,
				std::string("Cannot add values of types ") + lhs_->type()->type->getTypeName() + " " + rhs_->type()->type->getTypeName() + " can only add two values of the same type");
	}

	if (!(lhs_->type()->type->isPrimitive())) {
		throw StatementException(this, std::string("The add operator cannot be used with ") + lhs_->type()->type->getTypeName());
	}
}

int OperateStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int instrs = 0;

	switch (lhs_->type()->type->getType()) {
	case Int: {

		instrs = lhs_->generateCode(VM::vmTempRegisterOne, generated);

		generated << "pushr $" << VM::vmTempRegisterOne << " 1\n";
		instrs++;

		instrs += rhs_->generateCode(VM::vmTempRegisterTwo, generated);

		generated << "popr $" << VM::vmTempRegisterOne << " 1\n";
		instrs++;

		switch (op_) {

		case Add: {
			generated << "add $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
			instrs += 1;
			break;
		}

		case Subtract: {
			generated << "sub $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
			instrs += 1;
			break;
		}

		case Multiply: {
			generated << "mul $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
			instrs += 1;
			break;
		}

		case Divide: {
			generated << "div $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
			instrs += 1;
			break;
		}

		default: {
			throw StatementException(this, "Cannot generate int operation instruction");
			break;
		}

		}
		break;


	}
	case Float32: {
		instrs = lhs_->generateCode(VM::vmTempRegisterOne, generated);

		generated << "pushr $" << VM::vmTempRegisterOne << " 1\n";
		instrs++;

		instrs += rhs_->generateCode(VM::vmTempRegisterTwo, generated);

		generated << "popr $" << VM::vmTempRegisterOne << " 1\n";
		instrs++;

		switch (op_) {

		case Add: {
			generated << "addf32 $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
			instrs += 1;
			break;
		}

		case Subtract: {
			generated << "subf32 $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
			instrs += 1;
			break;
		}

		case Multiply: {
			generated << "mulf32 $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
			instrs += 1;
			break;
		}

		case Divide: {
			generated << "divf32 $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
			instrs += 1;
			break;
		}

		default: {
			throw StatementException(this, "Cannot generate float32 operation instruction");
			break;
		}

		}
		break;
	}


	default: {
		throw StatementException(this, "Operate statement cannot generate instruction for this type");
	}

	}

	return instrs;
}

}
