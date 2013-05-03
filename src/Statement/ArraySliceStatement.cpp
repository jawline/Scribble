/*
 * ArraySliceStatement.cpp
 *
 *  Created on: 3 May 2013
 *      Author: blake
 */

#include "ArraySliceStatement.hpp"
#include "Heap.hpp"
#include <Value/Array.hpp>
#include <Value/Int.hpp>

ArraySliceStatement::ArraySliceStatement(int line, std::string sym,
		SafeStatement array, SafeStatement start, SafeStatement end) :
		Statement(line, sym), array_(array), start_(start), end_(end) {

}

ArraySliceStatement::~ArraySliceStatement() {
	// TODO Auto-generated destructor stub
}

void ArraySliceStatement::checkTree(Type* functionType) {
	array_->checkTree(functionType);
	start_->checkTree(functionType);
	end_->checkTree(functionType);

	if (array_->type()->getType() != Array) {
		throw StatementException(this, "Expecting array");
	}

	if (start_->type()->getType() != Int || end_->type()->getType() != Int) {
		throw StatementException(this, "Expecting int for start or end");
	}

}

Value* ArraySliceStatement::execute(std::vector<Value*> const& variables) {

	ArrayValue* array = (ArrayValue*) array_->execute(variables);
	IntValue* start = (IntValue*) start_->execute(variables);
	IntValue* end = (IntValue*) end_->execute(variables);

	if (end->value() > (int)array->getArrayData()->dataLength()) {
		throw StatementException(this, "Slice size cannot exceed array size");
	}

	if (start->value() >= end->value()) {
		throw StatementException(this, "Start value should not be greater than or equal to end value when generating a slice");
	}


	array->setArrayData(array->getArrayData(), start->value(), end->value()-start->value());

	valueHeap.free(start);
	valueHeap.free(end);

	return array;
}

Type* ArraySliceStatement::type() {
	return array_->type();
}
