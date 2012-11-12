#include "FloatStatement.hpp"
#include <Value/Value.hpp>

FloatStatement::FloatStatement(float floatValue) {
	floatValue_ = floatValue;
}

Value FloatStatement::Execute() {
	return Value(floatValue_);
}
