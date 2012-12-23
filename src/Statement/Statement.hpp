#ifndef _STATEMENT_DEF_H_
#define _STATEMENT_DEF_H_
#include <iostream>

class Value;

class Statement {
private:
public:
	Statement() {}
	virtual ~Statement() {}
	virtual std::string GenerateBytecode() = 0;
};

#endif //_STATEMENT_DEF_H_
