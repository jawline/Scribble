#include "FunctionStatement.hpp"

void FunctionStatement::checkTree(ValueType functionType) {

	if (func_->getFunction().Get() == 0) {
		throw StatementException(this, "Error, function has not been defined");
	}

	if (func_->getFunction()->numArgs() != args_.size()) {
		throw StatementException(this, "Invalid number of arguments");
	}

	for (unsigned int i = 0; i < args_.size(); ++i) {
		args_[i]->checkTree(functionType);

		if (func_->getFunction()->argType(i) != args_[i]->type()) {
			throw StatementException(this,
					"Argument type does not match function type");
		}

	}

}
