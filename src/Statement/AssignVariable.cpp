#include "AssignVariable.hpp"
#include "StatementException.hpp"
#include <sstream>

AssignVariableStatement::AssignVariableStatement(Variable* var,
		Statement* exp) {
	var_ = var;
	exp_ = exp;
}

AssignVariableStatement::~AssignVariableStatement() {
	delete exp_;
}

Value* AssignVariableStatement::execute() {
	Value* ex = exp_->execute();

	if (ex->type() != var_->type) {
		throw StatementException("Cannot assign incorrect type");
	}

	var_->value = exp_->execute();
	return var_->value->clone();
}
