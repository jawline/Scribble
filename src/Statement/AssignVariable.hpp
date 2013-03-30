#ifndef _ASSIGN_VARIABLE_DEF_H_
#define _ASSIGN_VARIABLE_DEF_H_
#include "Statement.hpp"
#include <Value/Variable.hpp>
#include <vector>

class AssignVariableStatement: public Statement {
private:
	SafeStatement exp_;
	Variable* var_;

public:
	AssignVariableStatement(int lineNo, std::string sym, Variable* var, SafeStatement exp);
	~AssignVariableStatement();
	Value* execute(std::vector<Value*> const& variables);

	ValueType type() {
		return exp_->type();
	}

	void checkTree(ValueType functionType);
};

#endif //_ASSIGN_VARIABLE_DEF_H_
