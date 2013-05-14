/*
 * ArrayStatement.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#include "ArrayStatement.hpp"
#include <Value/Array.hpp>
#include <Value/Util.hpp>
#include <Value/Int.hpp>
#include "Heap.hpp"

ArrayStatement::ArrayStatement(int line, std::string text, Type* type,
		SafeStatement length) :
		Statement(line, text), type_(type), length_(length) {
}

ArrayStatement::~ArrayStatement() {
	// TODO Auto-generated destructor stub
}

Value* ArrayStatement::execute(std::vector<Value*> const& variables) {

	IntValue* l = (IntValue*) length_->execute(variables);
	int length = l->value();
	valueHeap.free(l);

	SP<ArrayData> data = SP<ArrayData>(nullptr);

	if (length > 0) {

		Value** initial = new Value*[length];

		for (int i = 0; i < length; i++) {
			initial[i] = ValueUtil::generateValue(type_->getSubtype());
		}

		data = SP<ArrayData>(new ArrayData(length, initial));
	}

	ArrayValue* arr = (ArrayValue*) ValueUtil::generateValue(type_);
	arr->setArrayData(data, 0, length);
	return arr;
}

Type* ArrayStatement::type() {
	return type_;
}

void ArrayStatement::checkTree(Type* functionType) {
	length_->checkTree(functionType);

	if (length_->type()->getType() != Int) {
		throw new StatementException(this, "Error expected int for array size");
	}
}
