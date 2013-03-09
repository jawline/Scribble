#ifndef _STR_STATEMENT_DEF_H_
#define _STR_STATEMENT_DEF_H_
#include "Statement.hpp"
#include <Value/Value.hpp>

class StringStatement : public Statement {
private:
	std::string stringValue_;

public:
	StringStatement(std::string stringValue);
	Value* execute();

};

#endif //_STR_STATEMENT_DEF_H_
