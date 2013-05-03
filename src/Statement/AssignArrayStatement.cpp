/*
 * AssignArrayStatement.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#include "AssignArrayStatement.hpp"
#include "Heap.hpp"
#include <Value/Array.hpp>
#include <Value/Int.hpp>

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
		throw StatementException(this,
				"Error cannot array assign. This object is not an array");
	}

	if (position_->type()->getType() != Int) {
		throw StatementException(this, "Expecting integer index");
	}

	if (!array_->type()->getSubtype()->Equals(toAssign_->type())) {
		throw StatementException(this,
				"Cannot assign to array. Type is different to array type");
	}
}
