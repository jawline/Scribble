/*
 * StructureAssignElement.cpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#include "StructureAssignElement.hpp"
#include "Heap.hpp"
#include <Scribble/Value/Structure.hpp>
#include <Scribble/Value/StructureInfo.hpp>

StructureAssignElement::StructureAssignElement(int line, std::string token,
		SafeStatement lhs, SafeStatement rhs, std::string elem) :
		Statement(line, token), lhs_(lhs), rhs_(rhs), elementName_(elem) {

}

StructureAssignElement::~StructureAssignElement() {
}

void StructureAssignElement::fix() {

	if (lhs_->type()->getType() != StructureType) {
		return;
	}

	StructureInfo* type = (StructureInfo*) lhs_->type();

	elementIndex_ = type->getIndex(elementName_);

	if (elementIndex_ == -1) {
		throw StatementException(this, "Does not exist in structure");
	}

	elementType_ = type->getIndex(elementIndex_).second->type;

}

void StructureAssignElement::checkTree(Type* functionType) {
	lhs_->checkTree(functionType);
	rhs_->checkTree(functionType);

	if (lhs_->type()->getType() != StructureType) {

		char errorText[256];
		sprintf(errorText, "type %i is not a structure",
				lhs_->type()->getType());

		throw StatementException(this, errorText);
	}

	if (!elementType_->Equals(rhs_->type())) {
		throw StatementException(this, "Cannot assign to a different type");
	}

}

Value* StructureAssignElement::execute(std::vector<Value*> const& variables) {

	Structure* loadedStruct = (Structure*) lhs_->execute(variables);
	Value* result = rhs_->execute(variables);

	loadedStruct->data()->get(elementIndex_)->applyOperator(Assign, result);

	return result;
}

Type* StructureAssignElement::type() {
	return elementType_;
}
