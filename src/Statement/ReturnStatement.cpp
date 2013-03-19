/*
 * ReturnStatement.cpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#include "ReturnStatement.hpp"

ReturnStatement::ReturnStatement(int lineNo, std::string sym, Statement* stm) :
		Statement(lineNo, sym) {
	stm_ = stm;
}

ReturnStatement::~ReturnStatement() {
	// TODO Auto-generated destructor stub
}

void ReturnStatement::checkTree(ValueType functionType) {
	stm_->checkTree(functionType);

	if (functionType != stm_->type()) {
		throw StatementException(this,
				"Return type differs from function type");
	}
}

Value* ReturnStatement::execute(std::vector<Value*> const& variables) {
	Return r(stm_->execute(variables));
	throw r;
}
