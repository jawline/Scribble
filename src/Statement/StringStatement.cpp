#include "StringStatement.hpp"
#include <Value/String.hpp>

StringStatement::StringStatement(std::string stringValue) {
	stringValue_ = stringValue;
}

Value* StringStatement::execute() {
	return new StringValue(stringValue_);
}
