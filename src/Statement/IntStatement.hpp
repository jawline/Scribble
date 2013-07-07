#ifndef _INT_STATEMENT_DEF_H_
#define _INT_STATEMENT_DEF_H_
#include <sstream>
#include "Statement.hpp"
#include <Value/Int.hpp>
#include <Value/TypeManager.hpp>

class IntStatement: public Statement {
private:
	int intValue_;

public:
	IntStatement(int lineNo, std::string sym, int intValue);
	Value* execute(std::vector<Value*> const& variables);

	Type* type() {
		return getTypeManager().getType(Int);
	}

	void checkTree(Type* functionType);

	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif //_INT_STATEMENT_DEF_H_
