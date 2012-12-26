#include "LoadVariable.hpp"
#include <sstream>

LoadVariableStatement::LoadVariableStatement(int variableId) {
	variableId_ = variableId;
}

std::string LoadVariableStatement::GenerateBytecode() {
	std::stringstream generated;
	generated << "loadv ";
	generated << variableId_;
	return generated.str();
}
