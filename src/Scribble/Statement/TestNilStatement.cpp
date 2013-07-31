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
