#include "StoreVariable.hpp"
#include <sstream>

StoreVariableStatement::StoreVariableStatement(int variableId) {
	variableId_ = variableId;
}

std::string StoreVariableStatement::GenerateBytecode() {
	std::stringstream generated;
	generated << "storev ";
	generated << variableId_;
	return generated.str();
}
