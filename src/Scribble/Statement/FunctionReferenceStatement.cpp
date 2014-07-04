/*
 * FunctionReferenceStatement.cpp
 *
 *  Created on: 2 Apr 2014
 *      Author: blake
 */

#include "FunctionReferenceStatement.hpp"

namespace ScribbleCore {

FunctionReferenceStatement::FunctionReferenceStatement(int lineNo,
		std::string sym, SmartPointer<FunctionReference> func) : Statement(lineNo, sym), func_(func) {
}

FunctionReferenceStatement::~FunctionReferenceStatement() {
}

void FunctionReferenceStatement::checkTree(Type* functionType) {

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

	//Double check the args have been resolved properly
	if (!func_->getFunction()->getSignature().argumentsEqual(
			func_->getTargetArguments())) {
		throw StatementException(this,
				"The resolved function has incorrect arguments. This is an internal compiler issue.");
	}

}

TypeReference FunctionReferenceStatement::type() {

	printf("TODO: This generates potentially incorrect code. Fix this later\n");

	if (func_->getFunction().get() == nullptr) {
		return makeTypeReference(getTypeManager().getType(TypeUnresolved));
	}

	return func_->getFunction()->getSignature().getReturnType();
}

int FunctionReferenceStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	generated
			<< "load \"" + func_->getFunction()->getNamespace()
					+ VM::vmNamespaceSeperator + func_->getFunction()->getName()
					+ "\" $" << resultRegister << "\n";

	return 1;
}

} /* namespace ScribbleCore */
