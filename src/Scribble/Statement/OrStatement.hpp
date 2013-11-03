/*
 * OrStatement.hpp
 *
 *  Created on: Nov 3, 2013
 *      Author: blake
 */

#ifndef ORSTATEMENT_HPP_
#define ORSTATEMENT_HPP_
#include "Statement.hpp"

class OrStatement : public Statement {
public:
	OrStatement(int lineNo, std::string sym,
			SafeStatement leftHandSide, SafeStatement rightHandSide);
	virtual ~OrStatement();

	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual Type* type();
};

#endif /* ORSTATEMENT_HPP_ */
