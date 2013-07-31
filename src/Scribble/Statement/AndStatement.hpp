/*
 * AndStatement.hpp
 *
 *  Created on: 27 Apr 2013
 *      Author: blake
 */

#ifndef ANDSTATEMENT_HPP_
#define ANDSTATEMENT_HPP_
#include "Statement.hpp"

class AndStatement : public Statement{
private:
	SafeStatement lhs_, rhs_;

public:
	AndStatement(int lineNo, std::string sym, SafeStatement leftHandSide,
			SafeStatement rightHandSide);
	virtual ~AndStatement();

	Value* execute(std::vector<Value*> const& variables);
	Type* type();
	void checkTree(Type* functionType);
};

#endif /* ANDSTATEMENT_HPP_ */
