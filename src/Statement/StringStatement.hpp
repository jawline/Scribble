#ifndef _STR_STATEMENT_DEF_H_
#define _STR_STATEMENT_DEF_H_
#include "Statement.hpp"
#include <Value/Value.hpp>
#include <Value/TypeManager.hpp>

class StringStatement : public Statement {
private:
	std::string stringValue_;

public:
	StringStatement(int lineNo, std::string sym, std::string stringValue);
	Value* execute(std::vector<Value*> const& variables);

	Type* type() {
		return getTypeManager().getType(String);
	}

	void checkTree(Type* functionType);
	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif //_STR_STATEMENT_DEF_H_
