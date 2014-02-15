/*
 * TestNilStatemnt.hpp
 *
 *  Created on: 10 May 2013
 *      Author: blake
 */

#ifndef TESTNILSTATEMNT_HPP_
#define TESTNILSTATEMNT_HPP_
#include "Statement.hpp"

namespace ScribbleCore {

class TestNilStatement: public Statement {
private:
	SafeStatement statement_;

public:
	TestNilStatement(int line, std::string sym, SafeStatement stmt);
	virtual ~TestNilStatement();

	void checkTree(Type* functionType);
	Type* type();

	int generateCode(int result, std::stringstream& code);
};

}

#endif /* TESTNILSTATEMNT_HPP_ */
