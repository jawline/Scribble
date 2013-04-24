#ifndef _GET_VARIABLE_DEF_H_
#define _GET_VARIABLE_DEF_H_
#include "Statement.hpp"
#include <Value/Variable.hpp>

class GetVariableStatement: public Statement {
private:
	SP<Variable> var_;

public:
	GetVariableStatement(int lineNo, std::string sym, SP<Variable> var);
	~GetVariableStatement();
	Value* execute(std::vector<Value*> const& variables);

	Type* type();

	void checkTree(Type* functionType);
};

#endif //_GET_VARIABLE_DEF_H_
