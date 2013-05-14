/*
 * ThreadStatement.cpp
 *
 *  Created on: 10 May 2013
 *      Author: blake
 */

#include "ThreadStatement.hpp"
#include <Value/TypeManager.hpp>
#include "Heap.hpp"
#include <thread>

ThreadStatement::ThreadStatement(int lineno, std::string sym,
		std::vector<SafeStatement> statements) :
		Statement(lineno, sym), statements_(statements) {
}

ThreadStatement::~ThreadStatement() {
}

void ThreadStatement::checkTree(Type* functionType) {

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->checkTree(functionType);
	}

}

void ThreadStatement::executeThreaded(std::vector<Value*> const& valueCopies) {

	//BIT THAT SHOULD BE THREADED
	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->execute(valueCopies);
	}

	for (unsigned int i = 0; i < valueCopies.size(); i++) {
		delete valueCopies[i];
	}

}

Value* ThreadStatement::execute(std::vector<Value*> const& variables) {

	//PRE THREADING BIT
	std::vector<Value*> valueCopies;

	for (unsigned int i = 0; i < variables.size(); ++i) {
		valueCopies.push_back(variables[i]->clone());
	}

	std::thread t(&ThreadStatement::executeThreaded, this, valueCopies);
	t.detach();

	//PRE THREADING BIT
	return valueHeap.make(getVoidType());
}

Type* ThreadStatement::type() {
	return getVoidType();
}
