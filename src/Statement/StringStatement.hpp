#ifndef _STR_STATEMENT_DEF_H_
#define _STR_STATEMENT_DEF_H_
#include "Statement.hpp"
#include <Value/Value.hpp>

class StringStatement : public Statement {
private:
	std::string stringValue_;

public:
	StringStatement(int lineNo, std::string sym, std::string stringValue);
	Value* execute();

	ValueType type() {
		return String;
	}

	void checkTree(ValueType functionType);
};

#endif //_STR_STATEMENT_DEF_H_
