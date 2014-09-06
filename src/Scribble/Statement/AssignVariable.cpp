#include "AssignVariable.hpp"
#include "StatementException.hpp"
#include <sstream>
#include <VM/Constants.hpp>

namespace ScribbleCore {

AssignVariableStatement::AssignVariableStatement(int lineNo, std::string sym,
		SmartPointer<Variable> var, SafeStatement exp) :
		Statement(lineNo, sym), exp_(exp), var_(var) {
		}

AssignVariableStatement::~AssignVariableStatement() {
}

void AssignVariableStatement::checkTree(Type* functionType) {
	exp_->checkTree(functionType);

	if (!(var_->getType()->Equals(exp_->type()->type())
			|| exp_->type()->type()->getType() == NilType)) {

		throw StatementException(this,
				std::string("Cannot assign a ")
						+ exp_->type()->type()->getTypeName() + " expression to a "
						+ var_->getType()->getTypeName() + " variable");

	}

}

int AssignVariableStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	generated << "--set " << var_->getName() << "\n";

	//Assigning a variable in the VM is as simply as moving the result of the statement into the variables assigned slot in the registers.
	int num = exp_->generateCode(
			var_->getPosition() + VM::vmNumReservedRegisters, generated);

	generated << "--end set " << var_->getName() << " size " << num << "\n";

	return num;
}

}
