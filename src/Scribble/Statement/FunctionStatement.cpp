#include "FunctionStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>

void FunctionStatement::checkTree(Type* functionType) {

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

		if (!(func_->getFunction()->argType(i)->Equals(arg->type()))) {
			throw StatementException(this,
					"Argument type does not match function type");
		}

	}

}

Value* FunctionStatement::execute(std::vector<Value*> const& variables) {

	std::vector<Value*> pArgs;

	for (unsigned int i = 0; i < func_->getArgs().size(); i++) {
		SafeStatement arg = func_->getArgs()[i];
		pArgs.push_back(arg->execute(variables));
	}

	Value* res = func_->getFunction()->execute(pArgs);

	for (unsigned int i = 0; i < pArgs.size(); i++) {
		valueHeap.free(pArgs[i]);
	}

	return res;
}

Type* FunctionStatement::type() {

	if (func_->getFunction().Null()) {
		return getTypeManager().getType(TypeUnresolved);
	}

	return func_->getFunction()->getType();
}

int FunctionStatement::generateCode(int resultRegister,
		std::stringstream& generated) {
	generated << "pushr $" << VM::vmNumReservedRegisters << " " << numDeclaredVariables_ << "\n";
	int num = func_->getFunction()->debugCode(generated);
	generated << "popr $" << VM::vmNumReservedRegisters << " " << numDeclaredVariables_ << "\n";
	return num + 2;
}
