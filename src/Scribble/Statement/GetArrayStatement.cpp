/*
 * GetArrayStatement.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#include "GetArrayStatement.hpp"
#include <VM/Constants.hpp>
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

GetArrayStatement::GetArrayStatement(int line, std::string sym,
		SafeStatement array, SafeStatement index) :
		Statement(line, sym), array_(array), index_(index) {
	type_ = makeTypeReference(getTypeManager().getType(TypeUnresolved));
}

GetArrayStatement::~GetArrayStatement() {
}

TypeReference GetArrayStatement::type() {

	return type_;
}

void GetArrayStatement::fix() {

	if (array_->type()->type->getSubtypeReference()->type != nullptr) {
		type_->type = array_->type()->type->getSubtypeReference()->type;

	} else {
		printf("COULD NOT FIX GET ARRAY STATEMENT\n");
	}

}

void GetArrayStatement::checkTree(Type* functionType) {

	array_->checkTree(functionType);
	index_->checkTree(functionType);

	if (array_->type()->type->getType() != Array) {
		throw StatementException(this, "This supplied value is not an array");
	}

	if (index_->type()->type->getType() != Int) {
		throw StatementException(this, "Expected integer index");
	}

}

int GetArrayStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	//If the result is not going anywhere ( Like the expression a[0]; )
	//then optimise it out by not generating the aget statement.
	if (resultRegister != -1) {

		//Place a reference to the array in register slot 1
		int instrs = array_->generateCode(VM::vmTempRegisterOne, generated);

		//Push it to the stack incase getting the index uses that register
		generated << "pushr $" << VM::vmTempRegisterOne << " 1\n";
		instrs++;

		//Put the index value in register two
		instrs += index_->generateCode(VM::vmTempRegisterTwo, generated);

		//Pop back the reference to the array
		generated << "popr $" << VM::vmTempRegisterOne << " 1\n";
		instrs++;

		//Place the value of the array at the index in the result operator
		generated << "aget $" << VM::vmTempRegisterOne << " $"
				<< VM::vmTempRegisterTwo << " $" << resultRegister << "\n";
		instrs++;

		return instrs;

	} else {
		return 0;
	}
}

}
