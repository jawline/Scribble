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
#include <VM/Constants.hpp>

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

Type* StructureAssignElement::type() {
	return elementType_;
}

int StructureAssignElement::generateCode(int result, std::stringstream& code) {

	int instrs = lhs_->generateCode(VM::vmTempRegisterOne, code);

	code << "pushr $" << VM::vmTempRegisterOne << " 1\n";

	instrs += rhs_->generateCode(VM::vmTempRegisterThree, code);

	code << "popr $" << VM::vmTempRegisterOne << " 1\n";
	instrs++;

	code << "load " << elementIndex_ << " $" << VM::vmTempRegisterTwo << "\n";
	instrs++;

	code << "sset $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterTwo
			<< " $" << VM::vmTempRegisterThree << "\n";
	instrs++;

	return instrs;
}
