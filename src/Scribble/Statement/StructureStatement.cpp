/*
 * StructureStatement.cpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#include "StructureStatement.hpp"
#include <Scribble/Value/StructureInfo.hpp>
#include <VM/Constants.hpp>

namespace ScribbleCore {

StructureStatement::StructureStatement(int lineno, std::string token,
		TypeReference type, std::vector<SafeStatement> statements) :
		Statement(lineno, token), type_(type), statements_(statements) {

}

StructureStatement::~StructureStatement() {
	// TODO Auto-generated destructor stub
}

void StructureStatement::checkTree(Type* functionType) {

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->checkTree(functionType);
	}

	if (type()->getType() != StructureType) {
		throw StatementException(this, "Expected type to be structure.");
	}

	StructureInfo* info = (StructureInfo*) type();

	if (info->getNumIndexs() != statements_.size()) {
		throw StatementException(this, "Invalid number of arguments");
	}

	for (unsigned int i = 0; i < statements_.size(); ++i) {

		if (!statements_[i]->type()->Equals(info->getIndex(i).second->type)) {
			throw StatementException(this, "Invalid argument type");
		}

	}

}

Type* StructureStatement::type() {
	return type_->type;
}

int StructureStatement::generateCode(int result, std::stringstream& code) {

	int instrs = 0;

	//Create the structure reference
	code << "newstruct \"" << type()->getTypeName() << "\" $"
			<< VM::vmTempRegisterOne << "\n";
	instrs += 1;

	//For each argument in the constructor
	for (unsigned int i = 0; i < statements_.size(); i++) {

		//Push the array register
		code << "pushr $" << VM::vmTempRegisterOne << " 1\n";
		instrs++;

		// Put the arguments value in temp register 2
		instrs += statements_[i]->generateCode(VM::vmTempRegisterTwo, code);

		//Load the field index into a register
		code << "load " << i << " $" << VM::vmTempRegisterThree << "\n";
		instrs++;

		//Pop the array register
		code << "popr $" << VM::vmTempRegisterOne << " 1\n";
		instrs++;

		//Place the value into the structure field.
		code << "sset $" << VM::vmTempRegisterOne << " $"
				<< VM::vmTempRegisterThree << " $" << VM::vmTempRegisterTwo
				<< "\n";

		instrs++;
	}

	if (result != VM::vmTempRegisterOne) {

		//Move the array reference into the result register.
		code << "move $" << VM::vmTempRegisterOne << " $" << result << "\n";
		instrs++;

	}

	return instrs;
}

}
