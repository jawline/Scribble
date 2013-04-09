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

	if (func_->getFunction()->numArgs() != func_->getArgs().size()) {
		throw StatementException(this, "Invalid number of arguments");
	}

	for (unsigned int i = 0; i < func_->getArgs().size(); ++i) {
		SafeStatement arg = func_->getArgs()[i];
		arg->checkTree(functionType);

		if (func_->getFunction()->argType(i) != arg->type()) {
			throw StatementException(this,
					"Argument type does not match function type");
		}

	}

}
