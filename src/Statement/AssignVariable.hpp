#ifndef _ASSIGN_VARIABLE_DEF_H_
#define _ASSIGN_VARIABLE_DEF_H_
#include "Statement.hpp"
#include <Value/Variable.hpp>

class AssignVariableStatement: public Statement {
private:
	Variable* var_;
	Statement* exp_;

public:
	AssignVariableStatement(Variable* var, Statement* exp);
	~AssignVariableStatement();
	Value* execute();

	ValueType type() {
		return exp_->type();
	}
};

#endif //_ASSIGN_VARIABLE_DEF_H_
