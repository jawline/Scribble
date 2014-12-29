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
}

NilStatement::~NilStatement() {
}

void NilStatement::checkTree(Type* functionType) {

}

TypeReference NilStatement::type() {
    return makeTypeReference(getNilType());
}

int NilStatement::generateCode(int resultRegister, std::stringstream& generated) {
    ;
    generated << "load 0 $" << resultRegister << "\n";
    return 1;
}

} /* namespace ScribbleCore */
