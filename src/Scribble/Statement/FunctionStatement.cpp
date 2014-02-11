#include "FunctionStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

void FunctionStatement::checkTree(Type* functionType) {

	if (func_->getFunction().get() == nullptr) {

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

Type* FunctionStatement::type() {

	if (func_->getFunction().get() == nullptr) {
		return getTypeManager().getType(TypeUnresolved);
	}

	return func_->getFunction()->getType();
}

int FunctionStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int numInstructions = 0;

	generated << "pushr $" << VM::vmReturnResultRegister << " "
			<< VM::vmNumReservedRegisters + numDeclaredVariables_ << "\n";
	numInstructions++;

	for (unsigned int i = 0; i < func_->getArgs().size(); i++) {

		SafeStatement arg = func_->getArgs()[i];

		numInstructions += arg->generateCode(VM::vmTempRegisterThree,
				generated);

		generated << "pushr $" << VM::vmTempRegisterThree << " " << 1 << "\n";
		numInstructions += 1;
	}

	generated
			<< "call \"" + func_->getFunction()->getNamespace()
					+ VM::vmNamespaceSeperator + func_->getFunction()->getName()
					+ "\"\n";

	generated << "popr $" << VM::vmReturnResultRegister + 1 << " "
			<< VM::vmNumReservedRegisters + numDeclaredVariables_ - 1 << "\n";

	numInstructions += 2;

	//If resultRegister is -1 then the result should not be stored in a register. If it is already the result register then there is no need to move it.
	//Otherwise move the value to the desired result register

	if (resultRegister != -1 || VM::vmReturnResultRegister == resultRegister) {

		generated << "move $" << VM::vmReturnResultRegister << " $"
				<< resultRegister << "\n";

		numInstructions += 1;

	}

	//If the result register is the return register then pop the previous value of that register. If it is not then restore its value
	if ((int) VM::vmReturnResultRegister == resultRegister) {
		generated << "popn\n";
	} else {
		generated << "popr $" << VM::vmReturnResultRegister << " " << 1 << "\n";
	}

	numInstructions += 1;

	return numInstructions;
}
