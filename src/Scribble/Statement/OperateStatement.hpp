/*
 * AddStatement.hpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#ifndef OPERATESTATEMENT_HPP_
#define OPERATESTATEMENT_HPP_
#include "Statement.hpp"

namespace ScribbleCore {

class OperateStatement: public Statement {
private:
	SafeStatement lhs_, rhs_;
	ValueOperator op_;

public:
	OperateStatement(int lineNo, std::string symbol, ValueOperator op, SafeStatement lhs,
			SafeStatement rhs);
	virtual ~OperateStatement();

	TypeReference type();
	void checkTree(Type* functionType);

	int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif /* OPERATESTATEMENT_HPP_ */
