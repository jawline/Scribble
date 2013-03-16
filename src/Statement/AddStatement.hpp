/*
 * AddStatement.hpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#ifndef ADDSTATEMENT_HPP_
#define ADDSTATEMENT_HPP_
#include "Statement.hpp"

class AddStatement: public Statement {
private:
	SafeStatement lhs_, rhs_;

public:
	AddStatement(int lineNo, std::string symbol, SafeStatement lhs,
			SafeStatement rhs);
	virtual ~AddStatement();

	Value* execute();
	ValueType type();
	void checkTree(ValueType functionType);
};

#endif /* ADDSTATEMENT_HPP_ */
