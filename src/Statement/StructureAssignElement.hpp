/*
 * StructureAssignElement.hpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#ifndef STRUCTUREASSIGNELEMENT_HPP_
#define STRUCTUREASSIGNELEMENT_HPP_
#include "Statement.hpp"

class StructureAssignElement: public Statement {
private:

	SafeStatement lhs_, rhs_;

	std::string elementName_;
	int elementIndex_;
	Type* elementType_;

public:
	StructureAssignElement(int line, std::string tkn,
			SafeStatement lhs, SafeStatement rhs, std::string elem);
	virtual ~StructureAssignElement();

	virtual void fix();
	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual Type* type();
};

#endif /* STRUCTUREASSIGNELEMENT_HPP_ */
