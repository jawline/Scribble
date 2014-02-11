/*
 * IfStatement.hpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#ifndef IFSTATEMENT_HPP_
#define IFSTATEMENT_HPP_
#include "Statement.hpp"
#include <Pointers/SmartPointer.hpp>
#include <vector>
#include <Scribble/Value/TypeManager.hpp>

class IfStatement: public Statement {
private:
	SmartPointer<Statement> condition_;
	std::vector<SmartPointer<Statement>> ifTrueStatements_;
	std::vector<SmartPointer<Statement>> ifFalseStatements_;

public:
	IfStatement(int lineNo, std::string sym, SmartPointer<Statement> condition,
			std::vector<SmartPointer<Statement>> ifTrueStatements,
			std::vector<SmartPointer<Statement>> ifFalseStatements);
	virtual ~IfStatement();

	Type* type() {
		return getTypeManager().getType(Void);
	}

	void checkTree(Type* functionType);
	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif /* IFSTATEMENT_HPP_ */
