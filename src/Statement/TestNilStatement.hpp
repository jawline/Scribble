/*
 * TestNilStatemnt.hpp
 *
 *  Created on: 10 May 2013
 *      Author: blake
 */

#ifndef TESTNILSTATEMNT_HPP_
#define TESTNILSTATEMNT_HPP_
#include "Statement.hpp"

class TestNilStatement: public Statement {
private:
	SafeStatement statement_;

public:
	TestNilStatement(int line, std::string sym, SafeStatement stmt);
	virtual ~TestNilStatement();

	void checkTree(Type* functionType);
	Value* execute(std::vector<Value*> const& variables);
	Type* type();
};

#endif /* TESTNILSTATEMNT_HPP_ */
