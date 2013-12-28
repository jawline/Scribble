#ifndef _GET_VARIABLE_DEF_H_
#define _GET_VARIABLE_DEF_H_
#include "Statement.hpp"
#include <Scribble/Value/Variable.hpp>

class GetVariableStatement: public Statement {
private:
	SmartPointer<Variable> var_;

public:
	GetVariableStatement(int lineNo, std::string sym, SmartPointer<Variable> var);
	~GetVariableStatement();
	Value* execute(std::vector<Value*> const& variables);

	Type* type();

	void checkTree(Type* functionType);
	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif //_GET_VARIABLE_DEF_H_
