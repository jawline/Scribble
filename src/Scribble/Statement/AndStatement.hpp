/*
 * AndStatement.hpp
 *
 *  Created on: Nov 3, 2013
 *      Author: blake
 */

#ifndef ANDSTATEMENT_HPP_
#define ANDSTATEMENT_HPP_
#include "Statement.hpp"

class AndStatement: public Statement {
private:
	SafeStatement lhs_;
	SafeStatement rhs_;

public:
	AndStatement(int lineNo, std::string sym, SafeStatement leftHandSide,
			SafeStatement rightHandSide);
	virtual ~AndStatement();

	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual Type* type();

	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif /* ANDSTATEMENT_HPP_ */
