/*
 * NegativeStatement.cpp
 *
 *  Created on: 29 Apr 2013
 *      Author: blake
 */

#include "NegativeStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Value/Int.hpp>
#include <Scribble/Value/Float32.hpp>
#include <VM/Constants.hpp>

NegativeStatement::NegativeStatement(int line, std::string text,
		SafeStatement exp) :
		Statement(line, text), exp_(exp) {
}

NegativeStatement::~NegativeStatement() {
}

void NegativeStatement::checkTree(Type* functionType) {
	exp_->checkTree(functionType);

	if (exp_->type()->getType() == Int) {
	} else if (exp_->type()->getType() == Float32) {
	} else {
		throw StatementException(this,
				"Negate not implemented on type yet. TODO");
	}

}

Value* NegativeStatement::execute(std::vector<Value*> const& variables) {
	if (exp_->type()->getType() == Int) {
		IntValue* lhs = (IntValue*) exp_->execute(variables);
		lhs->setValue(-lhs->value());
		return lhs;
	} else if (exp_->type()->getType() == Float32) {
		Float32Value* lhs = (Float32Value*) exp_->execute(variables);
		lhs->setValue(-lhs->getValue());
		return lhs;
	}
}

Type* NegativeStatement::type() {
	return exp_->type();
}

int NegativeStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int instr = exp_->generateCode(VM::vmTempRegisterTwo, generated);

	if (resultRegister != -1) {

		generated << "load 0 $" << VM::vmTempRegisterOne << "\n";

		if (exp_->type()->getType() == Int) {

			generated << "sub $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";

		} else if (exp_->type()->getType() == Float32) {

			generated << "subf32 $" << VM::vmTempRegisterOne << " $"
					<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";

		} else {
			throw StatementException(this,
					"Code generation on negation of value not supported\n");
		}

		instr += 2;
	}

	return instr;
}
