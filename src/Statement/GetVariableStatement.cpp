#include "GetVariableStatement.hpp"

GetVariableStatement::GetVariableStatement(int lineNo, std::string sym, Variable* var) : Statement(lineNo, sym){
	var_ = var;
}

GetVariableStatement::~GetVariableStatement() {
}

Value* GetVariableStatement::execute() {
	return var_->getValue()->clone();
}

void GetVariableStatement::checkTree(ValueType functionType) {

}
