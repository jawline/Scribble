#include "GetVariableStatement.hpp"

GetVariableStatement::GetVariableStatement(int lineNo, std::string sym,
		SP<Variable> var) :
		Statement(lineNo, sym) {
	var_ = var;
}

GetVariableStatement::~GetVariableStatement() {
}

Value* GetVariableStatement::execute(std::vector<Value*> const& variables) {
	return variables[var_->getPosition()]->clone();
}

Type* GetVariableStatement::type() {
	return var_->getType();
}

void GetVariableStatement::checkTree(Type* functionType) {

	if (var_->getType()->getType() == TypeUnresolved) {
		throw StatementException(this, "Variable type has not been resolved.");
	}
}
