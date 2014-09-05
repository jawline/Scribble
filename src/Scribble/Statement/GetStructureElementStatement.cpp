/*
 * GetStructureElementStatement.cpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#include "GetStructureElementStatement.hpp"
#include <Scribble/Value/StructureInfo.hpp>
#include <VM/Constants.hpp>
#include "../Value/TypeManager.hpp"

namespace ScribbleCore {

GetStructureElementStatement::GetStructureElementStatement(int yylineno,
		std::string sym, SafeStatement stmt, std::string name) :
		Statement(yylineno, sym), statement_(stmt), elementName_(name), elementIndex_(
				0) {
	elementType_ = makeTypeReference(getTypeManager().getType(TypeUnresolved));
}

GetStructureElementStatement::~GetStructureElementStatement() {
}

void GetStructureElementStatement::checkTree(Type* functionType) {
	statement_->checkTree(functionType);

	if (statement_->type()->type->getType() != StructureType) {

		std::stringstream errorMsg;

		errorMsg << "the expression given is a "
				<< statement_->type()->type->getTypeName()
				<< " and is not a structure";

		throw StatementException(this, errorMsg.str());
	}
}

void GetStructureElementStatement::fix() {

	if (statement_->type()->type->getType() != StructureType) {
		return;
	}

	StructureInfo* type = (StructureInfo*) statement_->type()->type;

	elementIndex_ = type->getFieldIndex(elementName_);

	if (elementIndex_ == -1) {
		throw StatementException(this, "Does not exist in structure");
	}

	elementType_->type = type->getField(elementIndex_).second->type;
}

TypeReference GetStructureElementStatement::type() {
	return elementType_;
}

int GetStructureElementStatement::generateCode(int resultRegister,
		std::stringstream& code) {
	int instrs = 0;

	if (resultRegister != -1) {
		instrs += statement_->generateCode(VM::vmTempRegisterOne, code);

		code << "load " << elementIndex_ << " $" << VM::vmTempRegisterTwo
				<< "\n";
		instrs++;

		code << "sget $" << VM::vmTempRegisterOne << " $"
				<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
		instrs++;
	}

	return instrs;
}

}
