/*
 * GetArrayStatement.cpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#include "GetArrayStatement.hpp"
#include "Heap.hpp"
#include <Scribble/Value/Array.hpp>
#include <Scribble/Value/Int.hpp>
#include <VM/Constants.hpp>

GetArrayStatement::GetArrayStatement(int line, std::string sym,
		SafeStatement array, SafeStatement index) :
		Statement(line, sym), array_(array), index_(index) {

}

GetArrayStatement::~GetArrayStatement() {
}

Type* GetArrayStatement::type() {
	return array_->type()->getSubtype();
}

void GetArrayStatement::checkTree(Type* functionType) {
	array_->checkTree(functionType);
	index_->checkTree(functionType);

	if (array_->type()->getType() != Array) {
		throw StatementException(this, "This supplied value is not an array");
	}

	if (index_->type()->getType() != Int) {
		throw StatementException(this, "Expected integer index");
	}
}

int GetArrayStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	//If the result is not going anywhere ( Like the expression a[0]; )
	//then optimize it out by not generating the aget statement.
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
