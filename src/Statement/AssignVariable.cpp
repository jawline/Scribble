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

	Value* res = exp_->execute();
	var_->getValue()->applyOperator(Assign, res);
	return res;
}
