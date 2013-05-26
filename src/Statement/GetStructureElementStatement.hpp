/*
 * GetStructureElementStatement.hpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#ifndef GETSTRUCTUREELEMENTSTATEMENT_HPP_
#define GETSTRUCTUREELEMENTSTATEMENT_HPP_
#include "Statement.hpp"
#include <string>

class GetStructureElementStatement: public Statement {
private:

	SafeStatement statement_;

	std::string elementName_;
	int elementIndex_;
	Type* elementType_;

public:
	GetStructureElementStatement(int yylineno, std::string sym,
			SafeStatement stmt, std::string elementName);
	virtual ~GetStructureElementStatement();

	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual Type* type();
	virtual void fix();
};

#endif /* GETSTRUCTUREELEMENTSTATEMENT_HPP_ */
