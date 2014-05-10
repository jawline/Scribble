/*
 * StructureAssignElement.hpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#ifndef STRUCTUREASSIGNELEMENT_HPP_
#define STRUCTUREASSIGNELEMENT_HPP_
#include "Statement.hpp"

namespace ScribbleCore {

class StructureAssignElement: public Statement {
private:

	SafeStatement lhs_, rhs_;

	std::string elementName_;
	int elementIndex_;
	TypeReference elementType_;

public:
	StructureAssignElement(int line, std::string tkn,
			SafeStatement lhs, SafeStatement rhs, std::string elem);
	virtual ~StructureAssignElement();

	virtual void fix();
	virtual void checkTree(Type* functionType);
	virtual TypeReference type();


	virtual int generateCode(int result, std::stringstream& code);
};

}

#endif /* STRUCTUREASSIGNELEMENT_HPP_ */
