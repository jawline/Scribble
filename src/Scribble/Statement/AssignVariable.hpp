#ifndef _ASSIGN_VARIABLE_DEF_H_
#define _ASSIGN_VARIABLE_DEF_H_
#include "Statement.hpp"
#include <Scribble/Value/Variable.hpp>
#include <vector>

class AssignVariableStatement: public Statement {
private:
	SafeStatement exp_;SP<Variable> var_;

public:
	AssignVariableStatement(int lineNo, std::string sym, SP<Variable> var,
			SafeStatement exp);
	~AssignVariableStatement();
	Value* execute(std::vector<Value*> const& variables);

	Type* type() {
		return exp_->type();
	}

	void checkTree(Type* functionType);
	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif //_ASSIGN_VARIABLE_DEF_H_
