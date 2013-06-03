/*
 * GetStructureElementStatement.cpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#include "GetStructureElementStatement.hpp"
#include "Heap.hpp"
#include <Value/Structure.hpp>
#include <Value/StructureInfo.hpp>

GetStructureElementStatement::GetStructureElementStatement(int yylineno,
		std::string sym, SafeStatement stmt, std::string name) :
		Statement(yylineno, sym), statement_(stmt), elementName_(name), elementIndex_(
				0) {
}

GetStructureElementStatement::~GetStructureElementStatement() {
	// TODO Auto-generated destructor stub
}

void GetStructureElementStatement::checkTree(Type* functionType) {
	statement_->checkTree(functionType);

	if (statement_->type()->getType() != StructureType) {

		char errorText[256];
		sprintf(errorText, "type %i is not a structure",
				statement_->type()->getType());

		throw StatementException(this, errorText);
	}
}

void GetStructureElementStatement::fix() {

	if (statement_->type()->getType() != StructureType) {
		return;
	}

	StructureInfo* type = (StructureInfo*) statement_->type();

	elementIndex_ = type->getIndex(elementName_);

	if (elementIndex_ == -1) {
		throw StatementException(this, "Does not exist in structure");
	}

	elementType_ = type->getIndex(elementIndex_).second->type;

}

Value* GetStructureElementStatement::execute(
		std::vector<Value*> const& variables) {

	Structure* gen = (Structure*) statement_->execute(variables);

	if (gen->data().Null()) {
		throw StatementException(this, "nil pointer. gen->data is null");
	}

	Value* e = gen->data()->get(elementIndex_)->clone();

	valueHeap.free(gen);

	return e;
}

Type* GetStructureElementStatement::type() {
	return elementType_;
}
