/*
 * IncrementStatement.cpp
 *
 *  Created on: 27 Mar 2013
 *      Author: blake
 */

#include "IncrementStatement.hpp"
#include <Scribble/Value/Int.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

IncrementStatement::IncrementStatement(int line, std::string sym,
		SmartPointer<Variable> variable, IncrementType op, bool post) :
		Statement(line, sym), variable_(variable), operator_(op), post_(post) {
			oneVal_ = new IntValue(1);
		}

IncrementStatement::~IncrementStatement() {
}

void IncrementStatement::checkTree(Type* functionType) {

	if (variable_->getType()->getType() != Int) {
		throw StatementException(this, std::string("Cannot use the increment operator on type ") + variable_->getType()->getTypeName());
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

			//TODO: Inc operator

			generated << "inc $" << variable_->getPosition() + VM::vmNumReservedRegisters << "\n";
			instrs += 1;

			if (resultRegister != -1) {

				generated << "move $"
						<< variable_->getPosition() + VM::vmNumReservedRegisters
						<< " $" << resultRegister << "\n";

				instrs += 1;
			}

		} else {

			if (resultRegister != -1) {
				generated << "move $"
						<< variable_->getPosition() + VM::vmNumReservedRegisters
						<< " $" << resultRegister << "\n";
				instrs++;
			}

			//TODO: Inc operator
			generated << "inc $" << variable_->getPosition() + VM::vmNumReservedRegisters << "\n";
			instrs += 1;
		}

		break;

	case Decrement:

		if (post_) {

			generated << "dec $" << variable_->getPosition() + VM::vmNumReservedRegisters << "\n";
			instrs += 1;

			if (resultRegister != -1) {

				generated << "move $"
						<< variable_->getPosition() + VM::vmNumReservedRegisters
						<< " $" << resultRegister << "\n";

				instrs++;
			}

		} else {

			if (resultRegister != -1) {

				generated << "move $"
						<< variable_->getPosition() + VM::vmNumReservedRegisters
						<< " $" << resultRegister << "\n";

				instrs++;

			}

			generated << "dec $" << variable_->getPosition() + VM::vmNumReservedRegisters << "\n";
			instrs += 1;
		}

		break;

	}

	return instrs;
}
