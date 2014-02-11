/*
 * OrStatement.hpp
 *
 *  Created on: Nov 3, 2013
 *      Author: blake
 */

#ifndef ORSTATEMENT_HPP_
#define ORSTATEMENT_HPP_
#include "Statement.hpp"

class OrStatement: public Statement {
private:
	SafeStatement lhs_, rhs_;

public:
	OrStatement(int lineNo, std::string sym, SafeStatement leftHandSide,
			SafeStatement rightHandSide);
	virtual ~OrStatement();

	virtual void checkTree(Type* functionType);
	virtual Type* type();
	virtual int generateCode(int resultRegister, std::stringstream& generated);
};

#endif /* ORSTATEMENT_HPP_ */
