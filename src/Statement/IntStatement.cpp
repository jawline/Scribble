#include "IntStatement.hpp"
#include <Value/Value.hpp>
#include <sstream>


IntStatement::IntStatement(int intValue) {
	intValue_ = intValue;
}

std::string IntStatement::GenerateBytecode() {
	std::stringstream generated;

	generated << "pushi ";
	generated << intValue_;
	return generated.str();
}
