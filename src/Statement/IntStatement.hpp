#ifndef _INT_STATEMENT_DEF_H_
#define _INT_STATEMENT_DEF_H_
#include "Statement.hpp"

class IntStatement : public Statement {
private:
	int intValue_;

public:
	IntStatement(int intValue);
	virtual Value Execute();
};

#endif //_INT_STATEMENT_DEF_H_
