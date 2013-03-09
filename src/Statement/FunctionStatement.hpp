#ifndef _FUNCTION_STATEMENT_H_
#define _FUNCTION_STATEMENT_H_
#include "Statement.hpp"
#include <Pointers/SmartPointer.hpp>
#include <Function/Function.hpp>
#include <stdio.h>
#include <vector>

class FunctionStatement : public Statement {
private:
	SmartPointer<Function> func_;
	std::vector<SmartPointer<Statement>> args_;

public:
	FunctionStatement(SmartPointer<Function> function, std::vector<SmartPointer<Statement>> arguments) {
		func_ = function;
		args_ = arguments;
	}


	virtual Value* execute() {

		std::vector<Value*> pArgs;

		for (unsigned int i = 0; i < args_.size(); i++) {
			pArgs.push_back( args_[i]->execute() );
		}

		Value* res = func_->execute(pArgs);

		for (unsigned int i = 0; i < pArgs.size(); i++) {
			delete pArgs[i];
		}

		return res;
	}

};

#endif //_FUNCTION_STATEMENT_H
