/*
 * ForStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "ForStatement.hpp"
#include <Value/Bool.hpp>
#include <Value/Void.hpp>
#include <Statement/Heap.hpp>
#include <Value/TypeManager.hpp>

ForStatement::ForStatement(int lineNo, std::string sym, SafeStatement initial,
		SafeStatement condition, SafeStatement step,
		std::vector<SafeStatement> statements) :
		Statement(lineNo, sym) {
	initial_ = initial;
	condition_ = condition;
	step_ = step;
	statements_ = statements;

}

ForStatement::~ForStatement() {
	// TODO Auto-generated destructor stub
}

Value* ForStatement::execute(std::vector<Value*> const& variables) {

	valueHeap.free(initial_->execute(variables));

	BoolValue* condition;
	while ((condition = ((BoolValue*) condition_->execute(variables)))->value()) {
		valueHeap.free(condition);

		for (unsigned int i = 0; i < statements_.size(); ++i) {
			valueHeap.free(statements_[i]->execute(variables));
		}

		valueHeap.free(step_->execute(variables));
	}

	valueHeap.free(condition);

	return valueHeap.make(getVoidType());
}

Type* ForStatement::type() {
	return getTypeManager().getType(Void);
}

void ForStatement::checkTree(Type* functionType) {
	initial_->checkTree(functionType);
	condition_->checkTree(functionType);
	step_->checkTree(functionType);

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		statements_[i]->checkTree(functionType);
	}

	if (condition_->type()->getType() != Boolean) {
		throw StatementException(this,
				"For second paramater must evaluate to a boolean");
	}
}

int ForStatement::generateBody(std::stringstream& generated) {

	generated << "#FOR BODY\n";

	int instrs = 0;

	for (unsigned int i = 0; i < statements_.size(); ++i) {
		instrs += statements_[i]->generateCode(5, generated);
	}

	//Add the final step to the body
	generated << "#FOR STEP\n";
	instrs += step_->generateCode(5, generated);

	return instrs;
}

int ForStatement::generateCode(int resultRegister, std::stringstream& generated) {

	//Generate the for setup (Run the initialising statement)
	generated << "#FOR Setup\n";
	int instrs = initial_->generateCode(5, generated);

	//Store the number of instrs the setup has
	int setupOffset = instrs;

	//Generate the for test condition
	generated << "#FOR CONDITION\n";
	instrs += condition_->generateCode(5, generated);

	//Generate the for body in a seperate stringstream
	std::stringstream forbody;
	int bodyInstrs = generateBody(forbody);

	//Check whether that condition is true
	generated << "#FOR CONTINUE TEST\n";
	generated << "neq $5 1\n";
	generated << "jmpr " << (bodyInstrs + 2) << "\n";
	instrs += 3;

	//Insert the body of the for into the code
	instrs += bodyInstrs;

	generated << forbody.str();

	//Add the return jump
	generated << "jmpr " << -((instrs - setupOffset)) << "\n";
	instrs++;

	return instrs;
}
