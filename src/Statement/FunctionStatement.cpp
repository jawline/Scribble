#include "FunctionStatement.hpp"

void FunctionStatement::checkTree(ValueType functionType) {

	if (func_->getFunction().Get() == 0) {

		std::string error = "";

		if (func_->getNamespace().length() > 0) {
			error = std::string("Function ") + func_->getNamespace() + "."
					+ func_->getName() + " could not be resolved. "
					+ func_->getResolveIssue();
		} else {
			error = std::string("Function ") + func_->getName()
					+ " could not be resolved. " + func_->getResolveIssue();
		}

		throw StatementException(this,
				std::string("Function ") + func_->getNamespace() + "."
						+ func_->getName() + " could not be resolved. "
						+ func_->getResolveIssue());
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
