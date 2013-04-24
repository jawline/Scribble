/*
 * ArrayStatement.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#include "ArrayStatement.hpp"
#include <Value/Array.hpp>
#include <Value/Util.hpp>

ArrayStatement::ArrayStatement(int line, std::string text, Type* type, unsigned int length) : Statement(line, text),
		type_(type), length_(length) {
}

ArrayStatement::~ArrayStatement() {
	// TODO Auto-generated destructor stub
}

Value* ArrayStatement::execute(std::vector<Value*> const& variables) {

	Value** initial = new Value*[length_];

	for (unsigned int i = 0; i < length_; i++) {
		initial[i] = ValueUtil::generateValue(type_->getSubtype());
	}

	SP<ArrayData> data = SP<ArrayData>(new ArrayData(length_, initial));
	ArrayValue* arr = (ArrayValue*) ValueUtil::generateValue(type_);
	arr->setArrayData(data);
	return arr;
}

Type* ArrayStatement::type() {
	return type_;
}

void ArrayStatement::checkTree(Type* functionType) {

}
