/*
 * StructureStatement.cpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#include "StructureStatement.hpp"
#include "Heap.hpp"
#include <Scribble/Value/Structure.hpp>
#include <Scribble/Value/StructureInfo.hpp>
#include <Scribble/Value/StructureData.hpp>

StructureStatement::StructureStatement(int lineno, std::string token,
		TypeReference type, std::vector<SafeStatement> statements) :
		Statement(lineno, token), type_(type), statements_(statements) {

}

StructureStatement::~StructureStatement() {
	// TODO Auto-generated destructor stub
}

void StructureStatement::checkTree(Type* functionType) {

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->checkTree(functionType);
	}

	if (type()->getType() != StructureType) {
		throw StatementException(this, "Expected type to be structure.");
	}

	StructureInfo* info = (StructureInfo*) type();

	if (info->getNumIndexs() != statements_.size()) {
		throw StatementException(this, "Invalid number of arguments");
	}

	for (unsigned int i = 0; i < statements_.size(); ++i) {

		if (!statements_[i]->type()->Equals(info->getIndex(i).second->type)) {
			throw StatementException(this, "Invalid argument type");
		}

	}

}

Value* StructureStatement::execute(std::vector<Value*> const& variables) {

	Structure* gen = (Structure*) valueHeap.make(type());

	Value** initial = new Value*[statements_.size()];

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		initial[i] = statements_[i]->execute(variables);
	}

	SafeStructureData data = SafeStructureData(new StructureData(statements_.size(), initial));

	gen->setData(data);

	return gen;
}

Type* StructureStatement::type() {
	return type_->type;
}

int StructureStatement::generateCode(int result, std::stringstream& code) {
}
