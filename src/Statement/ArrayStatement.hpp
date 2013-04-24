/*
 * ArrayStatement.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef ARRAYSTATEMENT_HPP_
#define ARRAYSTATEMENT_HPP_
#include "Statement.hpp"

class ArrayStatement: public Statement {
private:
	Type* type_;
	unsigned int length_;

public:
	ArrayStatement(int line, std::string text, Type* type, unsigned int length);
	virtual ~ArrayStatement();

	Value* execute(std::vector<Value*> const& variables);
	Type* type();

	void checkTree(Type* functionType);
};

#endif /* ARRAYSTATEMENT_HPP_ */
