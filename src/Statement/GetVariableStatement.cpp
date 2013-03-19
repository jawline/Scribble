#include "GetVariableStatement.hpp"

GetVariableStatement::GetVariableStatement(int lineNo, std::string sym, Variable* var) : Statement(lineNo, sym){
	var_ = var;
}

GetVariableStatement::~GetVariableStatement() {
}

Value* GetVariableStatement::execute(std::vector<Value*> const& variables) {
	return var_->getValue()->clone();
}

ValueType GetVariableStatement::type() {
	return var_->getType();
}

void GetVariableStatement::checkTree(ValueType functionType) {

}
