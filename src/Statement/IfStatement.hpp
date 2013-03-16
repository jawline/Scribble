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

class IfStatement: public Statement {
private:
	SP<Statement> condition_;
	std::vector<SP<Statement>> ifTrueStatements_;
	std::vector<SP<Statement>> ifFalseStatements_;

public:
	IfStatement(int lineNo, std::string sym, SP<Statement> condition,
			std::vector<SP<Statement>> ifTrueStatements,
			std::vector<SP<Statement>> ifFalseStatements);
	virtual ~IfStatement();

	Value* execute();

	ValueType type() {
		return Void;
	}

	void checkTree(ValueType functionType);
};

#endif /* IFSTATEMENT_HPP_ */
