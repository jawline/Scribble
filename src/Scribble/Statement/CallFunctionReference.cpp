/*
 * CallFunctionReference.cpp
 *
 *  Created on: 5 Jun 2014
 *      Author: blake
 */

#include "CallFunctionReference.hpp"

namespace ScribbleCore {

CallFunctionReference::CallFunctionReference(int lineNo, std::string sym,
		SafeStatement fn, std::vector<SafeStatement> args) :
		Statement(lineNo, sym), fn_(fn), args_(args) {

}

CallFunctionReference::~CallFunctionReference() {
}

void CallFunctionReference::checkTree(Type* functionType) {

	fn_->checkTree(functionType);

	for (unsigned int i = 0; i < args_.size(); i++) {
		args_[i]->checkTree(functionType);
	}

	if (fn_->type()->type->getType() != FunctionReferenceType) {
		throw StatementException(this, "Call cannot be used on a non function reference\n");
	}

}

TypeReference CallFunctionReference::type() {
	return fn_->type()->type->getReferenceReturnType();
}

int CallFunctionReference::generateCode(int resultRegister,
		std::stringstream& generated) {
	generated << "ERROR CANNOT GENERATE YET\n";
}

} /* namespace ScribbleCore */
