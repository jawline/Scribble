/*
 * IfStatement.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: blake
 */

#include "IfStatement.hpp"
#include <Scribble/Value/Bool.hpp>
#include <Scribble/Value/Void.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Statement/ReturnStatement.hpp>
#include <VM/Constants.hpp>

IfStatement::IfStatement(int lineNo, std::string sym, SmartPointer<Statement> condition,
		std::vector<SmartPointer<Statement>> ifTrueStatements,
		std::vector<SmartPointer<Statement>> ifFalseStatements) :
		Statement(lineNo, sym) {
	condition_ = condition;
	ifTrueStatements_ = ifTrueStatements;
	ifFalseStatements_ = ifFalseStatements;
}

IfStatement::~IfStatement() {
}

Value* IfStatement::execute(std::vector<Value*> const& variables) {

	BoolValue* v = (BoolValue*) condition_->execute(variables);
	bool val = v->value();
	valueHeap.free(v);

	if (val) {

		for (unsigned int i = 0; i < ifTrueStatements_.size(); ++i) {
			valueHeap.free(ifTrueStatements_[i]->execute(variables));
		}

	} else {

		for (unsigned int i = 0; i < ifFalseStatements_.size(); i++) {
			valueHeap.free(ifFalseStatements_[i]->execute(variables));
		}

	}

	return valueHeap.make(getVoidType());
}

void IfStatement::checkTree(Type* functionType) {
	condition_->checkTree(functionType);

	if (condition_->type()->getType() != Boolean) {
		throw StatementException(this, "If statement needs boolean condition");
	}

	for (unsigned int i = 0; i < ifTrueStatements_.size(); ++i) {
		ifTrueStatements_[i]->checkTree(functionType);
	}

	for (unsigned int i = 0; i < ifFalseStatements_.size(); ++i) {
		ifFalseStatements_[i]->checkTree(functionType);
	}
}

int IfStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	int trueSize = 0;
	std::stringstream trueBody;

	for (unsigned int i = 0; i < ifTrueStatements_.size(); i++) {
		trueSize += ifTrueStatements_[i]->generateCode(-1, trueBody);
	}

	int falseSize = 0;
	std::stringstream falseBody;

	for (unsigned int i = 0; i < ifFalseStatements_.size(); ++i) {
		falseSize += ifFalseStatements_[i]->generateCode(-1, falseBody);
	}

	int instrs = 0;

	generated << "#if statement test\n";
	instrs += condition_->generateCode(VM::vmTempRegisterThree, generated);

	generated << "#if check test result\n";

	generated << "neq $" << VM::vmTempRegisterThree << " 1\n";
	generated << "jmpr " << (trueSize + 2) << "\n";
	instrs += 3;

	generated << "#if statement body\n";

	generated << trueBody.str();
	instrs += trueSize;

	generated << "jmpr " << (falseSize + 1) << "\n";
	instrs += 1;

	generated << "#if statement false body\n";

	generated << falseBody.str();
	instrs += falseSize;

	return instrs;
}
