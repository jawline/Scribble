/*
 * IncrementStatement.hpp
 *
 *  Created on: 27 Mar 2013
 *      Author: blake
 */

#ifndef INCREMENTSTATEMENT_HPP_
#define INCREMENTSTATEMENT_HPP_
#include "Statement.hpp"
#include <Value/Variable.hpp>

enum IncrementType {
	Increment, Decrement
};

class IncrementStatement: public Statement {
private:
	Variable* variable_;
	IncrementType operator_;
	bool post_;
	Value* oneVal_;

public:

	IncrementStatement(int line, std::string sym, Variable* statement,
			IncrementType op, bool post);
	virtual ~IncrementStatement();

	virtual void checkTree(ValueType functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual ValueType type();
};

#endif /* INCREMENTSTATEMENT_HPP_ */
