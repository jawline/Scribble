/*
 * AndStatement.hpp
 *
 *  Created on: Nov 3, 2013
 *      Author: blake
 */

#ifndef ANDSTATEMENT_HPP_
#define ANDSTATEMENT_HPP_
#include "Statement.hpp"

/**
 * The and statement returns true if the left and right hand expressions both
 * evaluate to true.
 *
 * If the left side is false then the right side will not be checked.
 */

class AndStatement: public Statement {
private:

	//The left hand statement to be checked.
	SafeStatement lhs_;

	//The right hand statement to be checked.
	SafeStatement rhs_;

public:

	AndStatement(int lineNo, std::string sym, SafeStatement leftHandSide,
			SafeStatement rightHandSide);

	virtual ~AndStatement();

	virtual void checkTree(Type* functionType);

	/**
	 * AndStatements type is boolean.
	 */

	virtual Type* type();

	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif /* ANDSTATEMENT_HPP_ */
