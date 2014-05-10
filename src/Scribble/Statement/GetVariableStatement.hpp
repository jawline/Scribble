#ifndef _GET_VARIABLE_DEF_H_
#define _GET_VARIABLE_DEF_H_
#include "Statement.hpp"
#include <Scribble/Value/Variable.hpp>

namespace ScribbleCore {

class GetVariableStatement: public Statement {
private:
	SmartPointer<Variable> var_;

public:
	GetVariableStatement(int lineNo, std::string sym, SmartPointer<Variable> var);
	~GetVariableStatement();
	TypeReference type();
	void checkTree(Type* functionType);
	int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif //_GET_VARIABLE_DEF_H_
