/*
 * AddStatement.hpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#ifndef ADDSTATEMENT_HPP_
#define ADDSTATEMENT_HPP_
#include "Statement.hpp"

class AddStatement: public Statement{
private:
	SafeStatement lhs_, rhs_;
public:
	AddStatement(SafeStatement lhs, SafeStatement rhs);
	virtual ~AddStatement();

	Value* execute();
	ValueType type();
};

#endif /* ADDSTATEMENT_HPP_ */
