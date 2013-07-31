/*
 * ArrayLengthStatement.hpp
 *
 *  Created on: 29 Apr 2013
 *      Author: blake
 */

#ifndef ARRAYLENGTHSTATEMENT_HPP_
#define ARRAYLENGTHSTATEMENT_HPP_
#include "Statement.hpp"

class ArrayLengthStatement: public Statement {
private:
	SafeStatement exp_;

public:
	ArrayLengthStatement(int line, std::string text, SafeStatement exp);
	virtual ~ArrayLengthStatement();

	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual Type* type();
};

#endif /* ARRAYLENGTHSTATEMENT_HPP_ */
