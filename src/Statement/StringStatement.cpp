#include "StringStatement.hpp"

StringStatement::StringStatement(std::string stringValue) {
	stringValue_ = stringValue;
}

std::string StringStatement::GenerateBytecode() {
	return std::string("pushs ") + stringValue_ + "\n";
}