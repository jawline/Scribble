/*
 * BoolStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "BoolStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

namespace ScribbleCore {

BoolStatement::BoolStatement(int lineNo, std::string sym, bool value) :
		Statement(lineNo, sym) {
	value_ = value;
}

BoolStatement::~BoolStatement() {
}

Type* BoolStatement::type() {
	return getTypeManager().getType(Boolean);
}

void BoolStatement::checkTree(Type* functionType) {
}

int BoolStatement::generateCode(int resultRegister,
		std::stringstream& generated) {


	if (resultRegister != -1) {

		if (value_) {
			generated << "load " << VM::vmTrue << " $" << resultRegister << "\n";
		} else {
			generated << "load " << VM::vmFalse << " $" << resultRegister << "\n";
		}

	}

	return 1;
}

}
