#ifndef _STATEMENT_DEF_H_
#define _STATEMENT_DEF_H_
#include <Pointers/SmartPointer.hpp>
#include <Value/Value.hpp>
#include <string>

class Statement {
private:
public:
	Statement() {}
	virtual ~Statement() {}

	virtual std::string generateDebugInformation() { 
		return "Error: Debug info for this type not finished";
	}

	virtual Value* execute() = 0;
	virtual ValueType type() = 0;
};

typedef SP<Statement> SafeStatement;

#endif //_STATEMENT_DEF_H_
