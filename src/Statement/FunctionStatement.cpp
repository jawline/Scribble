#include "FunctionStatement.hpp"

void FunctionStatement::checkTree(ValueType functionType) {

	if (func_->numArgs() != args_.size()) {
		throw StatementException(this, "Invalid number of arguments");
	}

	for (unsigned int i = 0; i < args_.size(); ++i) {
		args_[i]->checkTree(functionType);

		if (func_->argType(i) != args_[i]->type()) {
			throw StatementException(this, "Argument type does not match function type");
		}

	}

}
