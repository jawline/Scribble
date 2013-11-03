/*
 * OrStatement.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: blake
 */

#include "OrStatement.hpp"

OrStatement::OrStatement(int lineNo, std::string sym,
		SafeStatement leftHandSide, SafeStatement rightHandSide) :
		Statement(lineNo, sym) {

}

OrStatement::~OrStatement() {
	// TODO Auto-generated destructor stub
}

void OrStatement::checkTree(Type* functionType) {

}

Value* OrStatement::execute(std::vector<Value*> const& variables) {

}

Type* OrStatement::type() {

}
