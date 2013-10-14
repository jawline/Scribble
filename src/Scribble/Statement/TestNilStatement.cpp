/*
 * TestNilStatemnt.cpp
 *
 *  Created on: 10 May 2013
 *      Author: blake
 */

#include "TestNilStatement.hpp"
#include "Heap.hpp"
#include <Scribble/Value/Array.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

TestNilStatement::TestNilStatement(int line, std::string sym, SafeStatement stmt) :
		Statement(line, sym) {
	statement_ = stmt;
}

TestNilStatement::~TestNilStatement() {

}

void TestNilStatement::checkTree(Type* functionType) {
	statement_->checkTree(functionType);

	if (statement_->type()->getType() != Array) {
		throw StatementException(this, "Expecting array argument");
	}

}

Value* TestNilStatement::execute(std::vector<Value*> const& variables) {
	bool r = false;

	ArrayValue* stmt = (ArrayValue*) statement_->execute(variables);

	if (stmt->getArrayData().Null()) {
		r = true;
	}

	valueHeap.free(stmt);

	return valueHeap.make(r);
}

Type* TestNilStatement::type() {
	return getBooleanType();
}

int TestNilStatement::generateCode(int result, std::stringstream& code) {
	int instrs =  statement_->generateCode(VM::vmTempRegisterOne, code);

	code << "load 0 $" << VM::vmTempRegisterThree << "\n";
	instrs++;

	code << "eq $" << VM::vmTempRegisterOne << " $" << VM::vmTempRegisterThree << "\n";
	instrs += 1;

	code << "load 1 $" << VM::vmTempRegisterThree << "\n";
	instrs++;

	if (result != VM::vmTempRegisterThree) {
		code << "move $" << VM::vmTempRegisterThree << " $" << result << "\n";
		instrs++;
	}

	return instrs;
}
