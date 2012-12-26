#include "FloatStatement.hpp"
#include <Value/Value.hpp>
#include <sstream>

FloatStatement::FloatStatement(float floatValue) {
	floatValue_ = floatValue;
}

std::string FloatStatement::GenerateBytecode() {
	std::stringstream generated;
	generated << "pushf ";
	generated << floatValue_;
	return generated.str();
}
