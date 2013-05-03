/*
 * ArrayLengthStatement.cpp
 *
 *  Created on: 29 Apr 2013
 *      Author: blake
 */

#include "ArrayLengthStatement.hpp"
#include <Value/TypeManager.hpp>
#include "Heap.hpp"
#include <Value/Array.hpp>

ArrayLengthStatement::ArrayLengthStatement(int line, std::string text,
		SafeStatement exp) :
		Statement(line, text), exp_(exp) {

}

ArrayLengthStatement::~ArrayLengthStatement() {

}

void ArrayLengthStatement::checkTree(Type* functionType) {
	exp_->checkTree(functionType);

	if (exp_->type()->getType() != Array) {
		throw StatementException(this, "Cannot get length of non array");
	}

}

Value* ArrayLengthStatement::execute(std::vector<Value*> const& variables) {

	ArrayValue* v = (ArrayValue*) exp_->execute(variables);
	int l = 0;

	if (!v->getArrayData().Null()) {
		l = v->getLength();
	}

	valueHeap.free(v);
	return valueHeap.make(l);
}

Type* ArrayLengthStatement::type() {
	return getIntType();
}
