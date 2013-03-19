#ifndef _STATEMENT_DEF_H_
#define _STATEMENT_DEF_H_
#include "StatementException.hpp"
#include <Pointers/SmartPointer.hpp>
#include <Value/Value.hpp>
#include <vector>
#include <string>
#include <sstream>

class Statement {
private:
	int lineNumber_;
	std::string symbolName_;

public:

	Statement(int lineNumber, std::string symbol) {
		lineNumber_ = lineNumber;
		symbolName_ = symbol;
	}

	virtual ~Statement() {
	}

	virtual std::string generateDebugInformation() {
		std::stringstream stream;
		stream << "Line Number: ";
		stream << lineNumber_;
		stream << " Symbol: ";
		stream << symbolName_;
		return stream.str();
	}

	virtual void checkTree(ValueType functionType) = 0;
	virtual Value* execute(std::vector<Value*> const& variables) = 0;
	virtual ValueType type() = 0;
};

typedef SP<Statement> SafeStatement;

#endif //_STATEMENT_DEF_H_
