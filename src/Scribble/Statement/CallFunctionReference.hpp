/*
 * CallFunctionReference.hpp
 *
 *  Created on: 5 Jun 2014
 *      Author: blake
 */

#ifndef CALLFUNCTIONREFERENCE_HPP_
#define CALLFUNCTIONREFERENCE_HPP_
#include "Statement.hpp"

namespace ScribbleCore {

class CallFunctionReference: public Statement {
private:
	SafeStatement fn_;
	std::vector<SafeStatement> args_;

public:
	CallFunctionReference(int lineNo, std::string sym, SafeStatement fn,
			std::vector<SafeStatement> args);
	virtual ~CallFunctionReference();

	virtual void checkTree(Type* functionType);

	/**
	 * AndStatements type is boolean.
	 */

	virtual TypeReference type();

	int generateCode(int resultRegister, std::stringstream& generated);
};

} /* namespace ScribbleCore */
#endif /* CALLFUNCTIONREFERENCE_HPP_ */
