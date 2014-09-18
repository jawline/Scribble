/*
 * IncrementStatement.cpp
 *
 *  Created on: 27 Mar 2013
 *      Author: blake
 */

#include "IncrementStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

namespace ScribbleCore {

IncrementStatement::IncrementStatement(int line, std::string sym,
		SmartPointer<Variable> variable, IncrementType op, bool post) :
		Statement(line, sym), variable_(variable), operator_(op), post_(post) {
		}

IncrementStatement::~IncrementStatement() {
}

void IncrementStatement::checkTree(Type* functionType) {

	StatementAssert(this, variable_->getType()->getType() == Int,
			std::string("Cannot use the increment operator on type ")
					+ variable_->getType()->getTypeName());
}

TypeReference IncrementStatement::type() {
	return makeTypeReference(getTypeManager().getType(Int));
}

int IncrementStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int instrs = 0;

	switch (operator_) {

	case Increment:

		if (post_) {

			//TODO: Inc operator

			generated << "inc $"
					<< variable_->getPosition() + VM::vmNumReservedRegisters
					<< "\n";
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
			generated << "inc $"
					<< variable_->getPosition() + VM::vmNumReservedRegisters
					<< "\n";
			instrs += 1;
		}

		break;

	case Decrement:

		if (post_) {

			generated << "dec $"
					<< variable_->getPosition() + VM::vmNumReservedRegisters
					<< "\n";
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

			generated << "dec $"
					<< variable_->getPosition() + VM::vmNumReservedRegisters
					<< "\n";
			instrs += 1;
		}

		break;

	}

	return instrs;
}

}
