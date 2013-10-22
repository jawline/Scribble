/*
 * TestStatement.hpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#ifndef TESTSTATEMENT_HPP_
#define TESTSTATEMENT_HPP_
#include "Statement.hpp"
#include <sstream>

enum TestType {
	TestEquals,
	TestAnd,
	TestNotEquals,
	TestGreater,
	TestLess,
	TestLessOrEqual,
	TestGreaterOrEqual
};

class TestStatement: public Statement {
private:
	TestType tType_;
	SafeStatement lhs_;
	SafeStatement rhs_;

public:
	TestStatement(int lineNo, std::string sym, TestType testType,
			SafeStatement leftHandSide, SafeStatement rightHandSide);
	virtual ~TestStatement();

	Value* execute(std::vector<Value*> const& variables);

	Type* type();
	void checkTree(Type* functionType);
	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif /* TESTSTATEMENT_HPP_ */
