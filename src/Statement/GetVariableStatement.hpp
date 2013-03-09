#ifndef _GET_VARIABLE_DEF_H_
#define _GET_VARIABLE_DEF_H_
#include "Statement.hpp"
#include <Value/Variable.hpp>

class GetVariableStatement : public Statement {
private:
	Variable* var_;

public:
	GetVariableStatement(Variable* var);
	~GetVariableStatement();
	Value* execute();
};


#endif //_GET_VARIABLE_DEF_H_
