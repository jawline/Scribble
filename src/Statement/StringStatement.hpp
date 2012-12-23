#ifndef _STR_STATEMENT_DEF_H_
#define _STR_STATEMENT_DEF_H_
#include "Statement.hpp"

class StringStatement : public Statement {
private:
	std::string stringValue_;

public:
	StringStatement(std::string stringValue);
	virtual std::string GenerateBytecode();
};

#endif //_STR_STATEMENT_DEF_H_
