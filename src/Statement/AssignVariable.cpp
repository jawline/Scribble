#include "AssignVariable.hpp"
#include <sstream>

AssignVariableStatement::AssignVariableStatement(int variableId, Statement* exp) {
	variableId_ = variableId;
	exp_ = exp;
}

AssignVariableStatement::~AssignVariableStatement() {
	delete exp_;
}

std::string AssignVariableStatement::GenerateBytecode() {
	std::stringstream generated;
	generated << exp_->GenerateBytecode() << "\n"; 
	generated << "storev ";
	generated << variableId_;
	return generated.str();
}
