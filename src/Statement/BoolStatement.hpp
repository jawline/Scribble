/*
 * BoolStatement.hpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#ifndef BOOLSTATEMENT_HPP_
#define BOOLSTATEMENT_HPP_
#include "Statement.hpp"

class BoolStatement: public Statement {
private:
	bool value_;

public:
	BoolStatement(int lineNo, std::string sym, bool value);
	virtual ~BoolStatement();

	Value* execute();
	ValueType type();

	void checkTree(ValueType functionType);
};

#endif /* BOOLSTATEMENT_HPP_ */
