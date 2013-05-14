/*
 * ThreadStatement.hpp
 *
 *  Created on: 10 May 2013
 *      Author: blake
 */

#ifndef THREADSTATEMENT_HPP_
#define THREADSTATEMENT_HPP_
#include "Statement.hpp"
#include <vector>
#include <thread>

/**
 * This statement will run the list of statements it is given in a separate thread. Returns Void
 */

class ThreadStatement: public Statement {
private:
	std::vector<SafeStatement> statements_;

	virtual void executeThreaded(std::vector<Value*> const& variables);

public:
	ThreadStatement(int lineno, std::string sym,
			std::vector<SafeStatement> statements);
	virtual ~ThreadStatement();

	virtual void checkTree(Type* functionType);
	virtual Value* execute(std::vector<Value*> const& variables);
	virtual Type* type();
};

#endif /* THREADSTATEMENT_HPP_ */
