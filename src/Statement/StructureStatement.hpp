/*
 * StructureStatement.hpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#ifndef STRUCTURESTATEMENT_HPP_
#define STRUCTURESTATEMENT_HPP_
#include "Statement.hpp"

class StructureStatement: public Statement {
private:
	Type* type_;
	std::vector<SafeStatement> statements_;

public:
	StructureStatement(int lineno, std::string token, Type* type, std::vector<SafeStatement> initials);
	virtual ~StructureStatement();

	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual Type* type();
};

#endif /* STRUCTURESTATEMENT_HPP_ */
