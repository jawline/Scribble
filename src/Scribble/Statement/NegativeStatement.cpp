/*
 * NegativeStatement.cpp
 *
 *  Created on: 29 Apr 2013
 *      Author: blake
 */

#include "NegativeStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Value/Int.hpp>

NegativeStatement::NegativeStatement(int line, std::string text,
		SafeStatement exp) :
		Statement(line, text), exp_(exp) {
}

NegativeStatement::~NegativeStatement() {
}

void NegativeStatement::checkTree(Type* functionType) {
	exp_->checkTree(functionType);

	if (exp_->type()->getType() != Int) {

		throw StatementException(this,
				"Negate not implemented on type yet. TODO");

	}

}

Value* NegativeStatement::execute(std::vector<Value*> const& variables) {
	IntValue* lhs = (IntValue*)exp_->execute(variables);
	lhs->setValue(-lhs->value());
	return lhs;
}

Type* NegativeStatement::type() {
	return exp_->type();
}
