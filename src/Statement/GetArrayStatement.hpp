/*
 * GetArrayStatement.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef GETARRAYSTATEMENT_HPP_
#define GETARRAYSTATEMENT_HPP_
#include "Statement.hpp"

class GetArrayStatement: public Statement {
private:
	SafeStatement array_;
	SafeStatement index_;

public:
	GetArrayStatement(int line, std::string sym, SafeStatement array, SafeStatement index);
	virtual ~GetArrayStatement();

	Value* execute(std::vector<Value*> const& variables);
	Type* type();

	void checkTree(Type* functionType);
};

#endif /* GETARRAYSTATEMENT_HPP_ */
