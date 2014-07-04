#ifndef _STATEMENT_DEF_H_
#define _STATEMENT_DEF_H_
#include "StatementException.hpp"
#include <Pointers/SmartPointer.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "../Function/FunctionSignature.hpp"
#include "../Parser/TypeReference.hpp"

namespace ScribbleCore {

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

	/**
	 * The type function has to return a type reference so that signatures for function calls & references.
	 */

	virtual TypeReference type() = 0;

	/**
	 * Extended by Statements which need 'fixing' later (Have type information added after other data has been evaluated).
	 * Only called if the statement is added to the parsers Fixable references list
	 */

	virtual void fix() {
	}

	virtual int generateCode(int resultRegister, std::stringstream& generated) {
		printf("Unimplemented statement %s!!\n", symbolName_.c_str());
		generated << std::string("#") + symbolName_ + " UNIMP\n";

		throw StatementException(this,
				"generate code is not implemented for this statement");

		return 1;
	}
};

typedef SmartPointer<Statement> SafeStatement;

}

#endif //_STATEMENT_DEF_H_
