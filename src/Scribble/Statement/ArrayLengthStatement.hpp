/*
 * ArrayLengthStatement.hpp
 *
 *  Created on: 29 Apr 2013
 *      Author: blake
 */

#ifndef ARRAYLENGTHSTATEMENT_HPP_
#define ARRAYLENGTHSTATEMENT_HPP_
#include "Statement.hpp"

/**
 * This statement takes a statement which returns an array and returns the length of that array.
 */

class ArrayLengthStatement: public Statement {
private:

	/**
	 * The statement which returns the array.
	 */

	SafeStatement exp_;

public:

	/**
	 * Construct an array length statement.
	 * @param line The line number on which the line occurs.
	 * @param text The The symbol in which this statement occurs.
	 * @param exp The array expression.
	 */

	ArrayLengthStatement(int line, std::string text, SafeStatement exp);
	virtual ~ArrayLengthStatement();

	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);

	/**
	 * The type will be an integer.
	 * @return The int type.
	 */

	virtual Type* type();
};

#endif /* ARRAYLENGTHSTATEMENT_HPP_ */
