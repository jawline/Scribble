#include "GetVariableStatement.hpp"

GetVariableStatement::GetVariableStatement(Variable* var) {
	var_ = var;
}

GetVariableStatement::~GetVariableStatement() {
}

Value* GetVariableStatement::execute() {
	return var_->getValue()->clone();
}
