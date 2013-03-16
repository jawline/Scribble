#include "IntStatement.hpp"
#include <sstream>

IntStatement::IntStatement(int lineNo, std::string sym, int intValue) :
		Statement(lineNo, sym) {
	intValue_ = intValue;
}

Value* IntStatement::execute() {
	return new IntValue(intValue_);
}

void IntStatement::checkTree(ValueType functionType) {

}
