/*
 * AndStatement.hpp
 *
 *  Created on: Nov 3, 2013
 *      Author: blake
 */

#ifndef ANDSTATEMENT_HPP_
#define ANDSTATEMENT_HPP_
#include "Statement.hpp"

/** FOR LATER
 * 		generated << "#And test\n";

		std::stringstream firstStatement;
		int firstInstrs = lhs_->generateCode(resultRegister, firstStatement);

		std::stringstream secondStatement;
		int secondInstrs = rhs_->generateCode(resultRegister, secondStatement);

		generated << firstStatement.str();
		instrs += firstInstrs;

		generated << "eqz $" << resultRegister << "\n";
		instrs++;

		generated << "jmpr " << 1 + secondInstrs << "\n";
		instrs++;

		generated << secondStatement.str();
		instrs += secondInstrs;

		//TODO: Needs to be verified

		generated << "#End of and test\n";
 */

class AndStatement: public Statement {
private:
	SafeStatement lhs_;
	SafeStatement rhs_;

public:
	AndStatement(int lineNo, std::string sym, SafeStatement leftHandSide,
			SafeStatement rightHandSide);
	virtual ~AndStatement();

	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual Type* type();

	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif /* ANDSTATEMENT_HPP_ */
