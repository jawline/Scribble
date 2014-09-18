#include "FunctionStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

namespace ScribbleCore {

FunctionStatement::FunctionStatement(int lineNo, std::string sym,
		SmartPointer<FunctionReference> function, std::vector<SafeStatement> args, int numDeclaredVariables) :
		Statement(lineNo, sym), numDeclaredVariables_(numDeclaredVariables) {
			func_ = function;
			args_ = args;
		}

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

	StatementAssert(this,
			func_->getFunction()->getSignature().argumentsEqual(
					func_->getTargetArguments()),
			"The resolved function has incorrect arguments. This is an internal compiler issue.");
}

TypeReference FunctionStatement::type() {
	return func_->getReturnType();
}

int FunctionStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int numInstructions = 0;

	generated << "pushr $" << VM::vmReturnResultRegister << " "
			<< VM::vmNumReservedRegisters + numDeclaredVariables_ << "\n";

	numInstructions++;

	for (unsigned int i = 0; i < args_.size(); i++) {

		SafeStatement arg = args_[i];

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

}
