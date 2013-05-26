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

	if (!statement_->type()->getType() != StructureType) {
		throw StatementException(this, "Not a structure");
	}

	StructureInfo* type = (StructureInfo*) statement_->type();

	elementIndex_ = type->getIndex(elementName_);

	if (elementIndex_ == -1) {
		throw StatementException(this, "Does not exist in structure");
	}

	elementType_ = type->getIndex(elementIndex_).second;
}

Value* GetStructureElementStatement::execute(std::vector<Value*> const& variables) {

	Structure* gen = (Structure*) statement_->execute(variables);

	if (gen->data().Null()) {
		throw StatementException(this, "Nil exception on structure");
	}

	Value* e = gen->data()->get(elementIndex_)->clone();

	valueHeap.free(gen);

	return e;
}

Type* GetStructureElementStatement::type() {
	return elementType_;
}
