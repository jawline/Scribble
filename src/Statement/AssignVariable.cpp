#include "AssignVariable.hpp"
#include "StatementException.hpp"
#include <sstream>

AssignVariableStatement::AssignVariableStatement(int lineNo, std::string sym,
		Variable* var, Statement* exp) :
		Statement(lineNo, sym) {
	var_ = var;
	exp_ = exp;
}

AssignVariableStatement::~AssignVariableStatement() {
	delete exp_;
}

Value* AssignVariableStatement::execute(std::vector<Value*> const& variables) {
	Value* ex = exp_->execute(variables);
	variables[var_->getPosition()]->applyOperator(Assign, ex);
	return ex;
}

void AssignVariableStatement::checkTree(ValueType functionType) {
	exp_->checkTree(functionType);

	if (var_->getType() != exp_->type()) {
		throw StatementException(this,
				"Cannot assign statement to a variable of a different type");
	}
}
