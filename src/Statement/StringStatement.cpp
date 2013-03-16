#include "StringStatement.hpp"
#include <Value/String.hpp>

StringStatement::StringStatement(int lineNo, std::string sym, std::string stringValue) : Statement(lineNo, sym) {
	stringValue_ = stringValue;
}

Value* StringStatement::execute() {
	return new StringValue(stringValue_);
}

void StringStatement::checkTree(ValueType functionType) {

}
