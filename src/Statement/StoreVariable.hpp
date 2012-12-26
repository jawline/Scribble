#ifndef _STORE_VARIABLE_DEF_H_
#define _STORE_VARIABLE_DEF_H_
#include "Statement.hpp"

class StoreVariableStatement : public Statement {
private:
	int variableId_;
public:
	StoreVariableStatement(int variableId);
	virtual std::string GenerateBytecode();
};

#endif //_STORE_VARIABLE_DEF_H_
