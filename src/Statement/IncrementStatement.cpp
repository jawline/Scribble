/*
 * IncrementStatement.cpp
 *
 *  Created on: 27 Mar 2013
 *      Author: blake
 */

#include "IncrementStatement.hpp"
#include <Value/Int.hpp>
#include <Value/TypeManager.hpp>

IncrementStatement::IncrementStatement(int line, std::string sym,
		SP<Variable> variable, IncrementType op, bool post) :
		Statement(line, sym), variable_(variable), operator_(op), post_(post) {
	oneVal_ = new IntValue(1);
}

IncrementStatement::~IncrementStatement() {
}

void IncrementStatement::checkTree(Type* functionType) {

	if (variable_->getType()->getType() != Int) {
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

Type* IncrementStatement::type() {
	return getTypeManager().getType(Int);
}

int IncrementStatement::generateCode(int resultRegister,
		std::stringstream& generated) {
	int instrs = 0;

	switch (operator_) {

	case Increment:

		if (post_) {

			generated << "add $" << variable_->getPosition() + 6 << " 1 $"
					<< variable_->getPosition() + 6 << "\n";

			generated << "move $" << variable_->getPosition() + 6 << " $"
					<< resultRegister << "\n";

			instrs += 3;
		} else {

			generated << "move $" << variable_->getPosition() + 6 << " $"
					<< resultRegister << "\n";

			generated << "add $" << variable_->getPosition() + 6 << " 1 $"
					<< variable_->getPosition() + 6 << "\n";

			instrs += 3;
		}

		break;

	case Decrement:

		if (post_) {

		} else {

		}

		break;

	}

	return instrs;
}
