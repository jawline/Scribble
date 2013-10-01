/*
 * ForStatement.cpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#include "ForStatement.hpp"
#include <Scribble/Value/Bool.hpp>
#include <Scribble/Value/Void.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <VM/Constants.hpp>

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
		instrs += statements_[i]->generateCode(-1, generated);
	}

	//Add the final step to the body
	generated << "#FOR STEP\n";
	instrs += step_->generateCode(-1, generated);

	return instrs;
}

int ForStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	//Generate the for setup (Run the initialising statement)
	generated << "#FOR Setup\n";
	int instrs = initial_->generateCode(-1, generated);

	//Store the number of instrs the setup has
	int setupOffset = instrs;

	//Generate the for test condition
	generated << "#FOR CONDITION\n";
	instrs += condition_->generateCode(VM::vmTempRegisterThree, generated);

	//Generate the for body in a seperate stringstream
	std::stringstream forbody;
	int bodyInstrs = generateBody(forbody);

	//Check whether that condition is true
	generated << "#FOR CONTINUE TEST\n";
	generated << "neq $" << VM::vmTempRegisterThree << " 1\n";
	generated << "jmpr " << (bodyInstrs + 2) << "\n";
	instrs += 4;

	//Insert the body of the for into the code
	generated << forbody.str();
	instrs += bodyInstrs;
	generated << "#body " << bodyInstrs << " instructions\n";

	//Add the return jump
	generated << "jmpr " << -((instrs - setupOffset)) << "\n";
	instrs++;

	generated << "#generated for statement " << instrs << " instructions\n";

	return instrs;
}
