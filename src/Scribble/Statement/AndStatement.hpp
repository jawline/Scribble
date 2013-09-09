/*
 * AndStatement.hpp
 *
 *  Created on: 27 Apr 2013
 *      Author: blake
 */

#ifndef ANDSTATEMENT_HPP_
#define ANDSTATEMENT_HPP_
#include "Statement.hpp"

/**
 * The and statement returns the & of the result of a left hand and right hand statement. If Left = Right then true otherwise false.
 */

class AndStatement: public Statement {
private:

	/**
	 * The left hand and right hand statements.
	 */

	SafeStatement lhs_, rhs_;

public:

	/**
	 * Construct an And statement.
	 * @param lineNo the line on which it occurs.
	 * @param sym The symbol in which it occurs.
	 * @param leftHandSide One of the two statements.
	 * @param rightHandSide the other statement.
	 */

	AndStatement(int lineNo, std::string sym, SafeStatement leftHandSide,
			SafeStatement rightHandSide);
	virtual ~AndStatement();

	Value* execute(std::vector<Value*> const& variables);

	/**
	 * The type will be a boolean.
	 * @return The boolean type
	 */

	Type* type();

	void checkTree(Type* functionType);
};

#endif /* ANDSTATEMENT_HPP_ */
