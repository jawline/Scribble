#ifndef _INT_STATEMENT_DEF_H_
#define _INT_STATEMENT_DEF_H_
#include "Statement.hpp"
#include <Value/Value.hpp>

class IntStatement: public Statement {
private:
	int intValue_;

public:
	IntStatement(int intValue);
	Value* execute();
};

#endif //_INT_STATEMENT_DEF_H_
