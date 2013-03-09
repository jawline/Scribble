#include "IntStatement.hpp"
#include <Value/Int.hpp>
#include <sstream>


IntStatement::IntStatement(int intValue) {
	intValue_ = intValue;
}

Value* IntStatement::execute() {
	return new IntValue(intValue_);
}
