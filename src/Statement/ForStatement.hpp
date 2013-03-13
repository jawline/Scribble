/*
 * ForStatement.hpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#ifndef FORSTATEMENT_HPP_
#define FORSTATEMENT_HPP_
#include "Statement.hpp"
#include <Pointers/SmartPointer.hpp>
#include <vector>

class ForStatement: public Statement {
private:
	SafeStatement initial_;
	SafeStatement condition_;
	SafeStatement step_;
	std::vector<SafeStatement> statements_;

public:
	ForStatement(SafeStatement initial, SafeStatement condition, SafeStatement step, std::vector<SafeStatement> statements);
	virtual ~ForStatement();

	Value* execute();
	ValueType type();
};

#endif /* FORSTATEMENT_HPP_ */
