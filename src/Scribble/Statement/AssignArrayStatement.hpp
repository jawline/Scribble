/*
 * AssignArrayStatement.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef ASSIGNARRAYSTATEMENT_HPP_
#define ASSIGNARRAYSTATEMENT_HPP_
#include "Statement.hpp"

class AssignArrayStatement: public Statement {
private:
	SafeStatement array_;
	SafeStatement toAssign_;
	SafeStatement position_;

public:

	AssignArrayStatement(int lineno, std::string text, SafeStatement array,
			SafeStatement assign, SafeStatement position);

	virtual ~AssignArrayStatement();

	Value* execute(std::vector<Value*> const& variables);
	Type* type();

	void checkTree(Type* functionType);
	int generateCode(int resultRegister, std::stringstream& generated);

};

#endif /* ASSIGNARRAYSTATEMENT_HPP_ */
