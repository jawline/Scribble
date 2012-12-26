#ifndef _LOAD_VARIABLE_DEF_H_
#define _LOAD_VARIABLE_DEF_H_
#include "Statement.hpp"

class LoadVariableStatement : public Statement {
private:
	int variableId_;

public:
	LoadVariableStatement(int variableId);
	virtual std::string GenerateBytecode();
};

#endif //_LOAD_VARIABLE_DEF_H_
