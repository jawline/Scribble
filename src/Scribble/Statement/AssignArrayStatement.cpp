/*
 * AssignArrayStatement.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#include "AssignArrayStatement.hpp"
#include "Heap.hpp"
#include <Scribble/Value/Array.hpp>
#include <Scribble/Value/Int.hpp>
#include <VM/Constants.hpp>

AssignArrayStatement::AssignArrayStatement(int lineno, std::string text,
		SafeStatement array, SafeStatement assign, SafeStatement position) :
		Statement(lineno, text), array_(array), toAssign_(assign), position_(
				position) {

}

AssignArrayStatement::~AssignArrayStatement() {
}

Value* AssignArrayStatement::execute(std::vector<Value*> const& variables) {

	ArrayValue* lhs = (ArrayValue*) array_->execute(variables);
	IntValue* pos = (IntValue*) position_->execute(variables);
	Value* rhs = toAssign_->execute(variables);

	if (pos->value() >= 0 && pos->value() < lhs->getLength()) {
		lhs->getArrayData()->index(lhs->getStart() + pos->value())->applyOperator(
				Assign, rhs);
	} else {
		throw StatementException(this, "Index out of bounds");
	}

	valueHeap.free(pos);
	valueHeap.free(rhs);
	return lhs;
}

Type* AssignArrayStatement::type() {
	return array_->type();
}

void AssignArrayStatement::checkTree(Type* functionType) {
	array_->checkTree(functionType);
	toAssign_->checkTree(functionType);
	position_->checkTree(functionType);

	if (array_->type()->getType() != Array) {
		throw StatementException(this, std::string("Not an array, Type ") + array_->type()->getTypeName() + " given when an array was expected.");
	}

	if (position_->type()->getType() != Int) {
		throw StatementException(this, std::string("Type ") + position_->type()->getTypeName() + " cannot be used as an index. Index must be an integer");
	}

	if (!array_->type()->getSubtype()->Equals(toAssign_->type())) {
		throw StatementException(this, std::string("Value given is of type ") + toAssign_->type()->getTypeName() + " which differs from expected type " + array_->type()->getSubtype()->getTypeName());
	}
}

int AssignArrayStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int instrs = toAssign_->generateCode(VM::vmTempRegisterOne, generated);

	generated << "pushr $" << VM::vmTempRegisterOne << " 1\n";
	instrs++;

	instrs += array_->generateCode(VM::vmTempRegisterTwo, generated);

	generated << "pushr $" << VM::vmTempRegisterTwo << " 1\n";
	instrs++;

	instrs += position_->generateCode(VM::vmTempRegisterThree, generated);

	generated << "popr $" << VM::vmTempRegisterTwo << " 1\n";
	generated << "popr $" << VM::vmTempRegisterOne << " 1\n";
	instrs += 2;

	generated << "aset $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo << " $" << VM::vmTempRegisterThree << "\n";
	instrs++;

	return instrs;
}
