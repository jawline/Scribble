/*
 * ReturnStatement.hpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#ifndef RETURNSTATEMENT_HPP_
#define RETURNSTATEMENT_HPP_
#include "Statement.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

class ReturnStatement: public Statement {
private:
	SafeStatement stm_;

public:
	ReturnStatement(int lineno, std::string symb, SafeStatement stm);
	virtual ~ReturnStatement();

	virtual void checkTree(Type* functionType);
	virtual Type* type() {
		return getTypeManager().getType(NilType);
	}

	int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif /* RETURNSTATEMENT_HPP_ */
