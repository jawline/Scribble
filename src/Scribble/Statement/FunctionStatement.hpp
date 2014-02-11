#ifndef _FUNCTION_STATEMENT_H_
#define _FUNCTION_STATEMENT_H_
#include "Statement.hpp"
#include <Scribble/Statement/Heap.hpp>
#include <Pointers/SmartPointer.hpp>
#include <API/Function.hpp>
#include <Scribble/Function/FunctionReference.hpp>
#include <VM/Constants.hpp>
#include <stdio.h>
#include <vector>

class FunctionStatement: public Statement {
private:
	SmartPointer<FunctionReference> func_;

	//This stores the number of declared variables when the function is called. This allows for the push/pop of registers to be optimized in the VM
	int numDeclaredVariables_;

public:
	FunctionStatement(int lineNo, std::string sym,
			SmartPointer<FunctionReference> function, int numDeclaredVariables) :
			Statement(lineNo, sym), numDeclaredVariables_(numDeclaredVariables) {
		func_ = function;
	}

	Type* type();

	void checkTree(Type* functionType);

	virtual int generateCode(int resultRegister, std::stringstream& generated);
};

#endif //_FUNCTION_STATEMENT_H
