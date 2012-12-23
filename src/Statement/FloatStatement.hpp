#ifndef _FLOAT_STATEMENT_DEF_H_
#define _FLOAT_STATEMENT_DEF_H_
#include "Statement.hpp"

class FloatStatement : public Statement {
private:
	float floatValue_;

public:
	
	FloatStatement(float floatValue);
	std::string GenerateBytecode();
};

#endif //_FLOAT_STATEMENT_DEF_H_
