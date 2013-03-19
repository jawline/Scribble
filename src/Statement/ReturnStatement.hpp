/*
 * ReturnStatement.hpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#ifndef RETURNSTATEMENT_HPP_
#define RETURNSTATEMENT_HPP_
#include "Statement.hpp"

class Return {
public:
	Return(Value* v) {
		val_ = v;
	}

	Value* val_;
};

class ReturnStatement: public Statement {
private:
	Statement* stm_;

public:
	ReturnStatement(int lineno, std::string symb, Statement* stm);
	virtual ~ReturnStatement();

	virtual void checkTree(ValueType functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual ValueType type() {
		return Void;
	}
};

#endif /* RETURNSTATEMENT_HPP_ */
