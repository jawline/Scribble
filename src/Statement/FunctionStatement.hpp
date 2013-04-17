#ifndef _FUNCTION_STATEMENT_H_
#define _FUNCTION_STATEMENT_H_
#include "Statement.hpp"
#include <Statement/Heap.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Function/Function.hpp>
#include <Function/FunctionReference.hpp>
#include <stdio.h>
#include <vector>

class FunctionStatement: public Statement {
private:
	SmartPointer<FunctionReference> func_;

public:
	FunctionStatement(int lineNo, std::string sym,
			SmartPointer<FunctionReference> function) :
			Statement(lineNo, sym) {
		func_ = function;
	}

	virtual Value* execute(std::vector<Value*> const& variables);
	ValueType type();

	void checkTree(ValueType functionType);
};

#endif //_FUNCTION_STATEMENT_H
