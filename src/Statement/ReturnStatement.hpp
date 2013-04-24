/*
 * ReturnStatement.hpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#ifndef RETURNSTATEMENT_HPP_
#define RETURNSTATEMENT_HPP_
#include "Statement.hpp"
#include <Value/TypeManager.hpp>

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

	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual Type* type() {
		return getTypeManager().getType(Void);
	}
};

#endif /* RETURNSTATEMENT_HPP_ */
