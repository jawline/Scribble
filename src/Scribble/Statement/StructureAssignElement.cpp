/*
 * StructureAssignElement.cpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#include "StructureAssignElement.hpp"
#include <Scribble/Value/StructureInfo.hpp>
#include <VM/Constants.hpp>

namespace ScribbleCore {

StructureAssignElement::StructureAssignElement(int line, std::string token,
		SafeStatement lhs, SafeStatement rhs, std::string elem) :
		Statement(line, token), lhs_(lhs), rhs_(rhs), elementName_(elem) {

}

StructureAssignElement::~StructureAssignElement() {
}

void StructureAssignElement::fix() {

	if (lhs_->type()->type->getType() != StructureType) {
		return;
	}

	StructureInfo* type = (StructureInfo*) lhs_->type()->type;

	elementIndex_ = type->getIndex(elementName_);

	if (elementIndex_ == -1) {
		throw StatementException(this, "Does not exist in structure");
	}

	elementType_ = type->getIndex(elementIndex_).second;
}

void StructureAssignElement::checkTree(Type* functionType) {
	lhs_->checkTree(functionType);
	rhs_->checkTree(functionType);

	if (lhs_->type()->type->getType() != StructureType) {

		std::stringstream errorMsg;
		errorMsg << "the expression given is a " << lhs_->type()->type->getTypeName() << " and is not a structure";

		throw StatementException(this, errorMsg.str());
	}

	if (!(elementType_->type->Equals(rhs_->type()->type) || rhs_->type()->type->getType() == NilType)) {
		std::stringstream errorMsg;
		errorMsg << "The structure field " << elementName_ << " is a " << elementType_->type->getTypeName() << " and cannot be assigned to a " << rhs_->type()->type->getTypeName() << " expression";
		throw StatementException(this, errorMsg.str());
	}

}

TypeReference StructureAssignElement::type() {
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

}
