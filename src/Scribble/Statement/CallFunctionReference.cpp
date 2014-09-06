/*
 * CallFunctionReference.cpp
 *
 *  Created on: 5 Jun 2014
 *      Author: blake
 */

#include "CallFunctionReference.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

CallFunctionReference::CallFunctionReference(int lineNo, std::string sym,
		SafeStatement fn, std::vector<SafeStatement> args,
		int numDeclaredVariables) :
		Statement(lineNo, sym), numDeclaredVariables_(numDeclaredVariables), fn_(
				fn), args_(args) {

	returnType_ = makeTypeReference(getTypeManager().getType(TypeUnresolved));
}

CallFunctionReference::~CallFunctionReference() {
}

void CallFunctionReference::checkTree(Type* functionType) {

	fn_->checkTree(functionType);

	for (unsigned int i = 0; i < args_.size(); i++) {
		args_[i]->checkTree(functionType);
	}

	if (fn_->type()->type()->getReferenceArguments().size() != args_.size()) {

		std::stringstream errorMsg;

		errorMsg << "the function takes "
				<< fn_->type()->type()->getReferenceArguments().size()
				<< " arguments however only " << args_.size()
				<< " where supplied";

		throw StatementException(this, errorMsg.str());
	}

	for (unsigned int i = 0;
			i < fn_->type()->type()->getReferenceArguments().size(); i++) {

		if (!fn_->type()->type()->getReferenceArguments()[i]->type()->Equals(
				args_[i]->type()->type())) {

			std::stringstream errorMsg;
			errorMsg << "argument " << i << "was expected to be a "
					<< fn_->type()->type()->getReferenceArguments()[0]->type()->getTypeName()
					<< " however a " << args_[i]->type()->type()->getTypeName()
					<< " was supplied";

			throw StatementException(this, errorMsg.str());
		}

	}

	if (fn_->type()->type()->getType() != FunctionReferenceType) {
		throw StatementException(this,
				std::string("value passed is a ")
						+ fn_->type()->type()->getTypeName()
						+ " and not a function reference");
	}

}

TypeReference CallFunctionReference::type() {
	return returnType_;
}

void CallFunctionReference::fix() {
	returnType_->setType(fn_->type()->type()->getReferenceReturnType()->type());
}

int CallFunctionReference::generateCode(int resultRegister,
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

	fn_->generateCode(VM::vmTempRegisterThree, generated);
	numInstructions++;

	generated << "call $" << VM::vmTempRegisterThree << "\n";

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

} /* namespace ScribbleCore */
