#ifndef _STR_STATEMENT_DEF_H_
#define _STR_STATEMENT_DEF_H_
#include "Statement.hpp"
#include <Scribble/Value/Value.hpp>
#include <Scribble/Value/TypeManager.hpp>

class StringStatement : public Statement {
private:
	std::string stringValue_;

public:
	StringStatement(int lineNo, std::string sym, std::string stringValue);

	Type* type() {
		return getTypeManager().getType(StringType);
	}

	void checkTree(Type* functionType);
	int generateCode(int resultRegister, std::stringstream& generated);
};

#endif //_STR_STATEMENT_DEF_H_
