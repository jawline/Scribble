/*
 * ArraySliceStatement.hpp
 *
 *  Created on: 3 May 2013
 *      Author: blake
 */

#ifndef ARRAYSLICESTATEMENT_HPP_
#define ARRAYSLICESTATEMENT_HPP_
#include "Statement.hpp"

class ArraySliceStatement: public Statement {
private:
	SafeStatement array_, start_, end_;

public:

	ArraySliceStatement(int line, std::string sym, SafeStatement array,
			SafeStatement start, SafeStatement end);

	virtual ~ArraySliceStatement();

	void checkTree(Type* functionType);
	Value* execute(std::vector<Value*> const& variables);
	Type* type();
};

#endif /* ARRAYSLICESTATEMENT_HPP_ */
