/*
 * NilStatement.cpp
 *
 *  Created on: 27 Feb 2014
 *      Author: blake
 */

#include "NilStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

NilStatement::NilStatement(int lineNo, std::string symbol) : Statement(lineNo, symbol) {
	// TODO Auto-generated constructor stub

}

NilStatement::~NilStatement() {
	// TODO Auto-generated destructor stub
}

void NilStatement::checkTree(Type* functionType) {

}

Type* NilStatement::type() {
	return getVoidType();
}

int NilStatement::generateCode(int resultRegister, std::stringstream& generated) {;
	generated << "load 0 $" << resultRegister << "\n";
	return 1;
}

} /* namespace ScribbleCore */
