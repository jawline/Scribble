#ifndef _STATEMENT_DEF_H_
#define _STATEMENT_DEF_H_
#include "StatementException.hpp"
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Value/Value.hpp>
#include <iostream>
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

	virtual void checkTree(Type* functionType) = 0;
	virtual Type* type() = 0;

	virtual int generateCode(int resultRegister, std::stringstream& generated) {
		printf("Unimplemented statement %s!!\n", symbolName_.c_str());
		generated << std::string("#") + symbolName_ + " UNIMP\n";

		throw StatementException(this, "generate code is not implemented for this statement");

		return 1;
	}
};

typedef SmartPointer<Statement> SafeStatement;

#endif //_STATEMENT_DEF_H_
