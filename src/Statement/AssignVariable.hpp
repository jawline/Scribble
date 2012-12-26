#ifndef _ASSIGN_VARIABLE_DEF_H_
#define _ASSIGN_VARIABLE_DEF_H_
#include "Statement.hpp"

class AssignVariableStatement : public Statement {
private:
	int variableId_;
	Statement* exp_;

public:
	AssignVariableStatement(int variableId, Statement* exp);
	~AssignVariableStatement();
	virtual std::string GenerateBytecode();
};


#endif //_ASSIGN_VARIABLE_DEF_H_
