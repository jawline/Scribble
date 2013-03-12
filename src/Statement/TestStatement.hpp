/*
 * TestStatement.hpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#ifndef TESTSTATEMENT_HPP_
#define TESTSTATEMENT_HPP_
#include "Statement.hpp"

enum TestType {
	TestEquals, TestGreater, TestLess
};

class TestStatement: public Statement {
private:
	TestType tType_;
	Statement* lhs_;
	Statement* rhs_;

public:
	TestStatement(TestType testType, Statement* leftHandSide,
			Statement* rightHandSide);
	virtual ~TestStatement();

	Value* execute();

	ValueType type();

};

#endif /* TESTSTATEMENT_HPP_ */
