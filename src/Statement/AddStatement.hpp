#ifndef _ADD_STATEMENT_DEF_H_
#define _ADD_STATEMENT_DEF_H_
#include "Statement.hpp"

class AddStatement : public Statement {
private:
	Statement* lhs_, *rhs_;
public:
	AddStatement(Statement* lhs, Statement* rhs);
	~AddStatement();


	virtual Value Execute();

};

#endif //_ADD_STATEMENT_DEF_H_
