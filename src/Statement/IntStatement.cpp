#include "IntStatement.hpp"
#include <sstream>

IntStatement::IntStatement(int lineNo, std::string sym, int intValue) :
		Statement(lineNo, sym) {
	intValue_ = intValue;
}

Value* IntStatement::execute(std::vector<Value*> const& variables) {
	return new IntValue(intValue_);
}

void IntStatement::checkTree(ValueType functionType) {

}
