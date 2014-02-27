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

	if (!(var_->getType()->Equals(exp_->type()) || exp_->type()->getType() == NilType)) {

		throw StatementException(this,
				std::string("Cannot assign value of type ")
						+ exp_->type()->getTypeName() + " to variable of type "
						+ var_->getType()->getTypeName());

	}
}

int AssignVariableStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	//Assigning a variable in the VM is as simply as moving the result of the statement into the variables assigned slot in the registers.
	return exp_->generateCode(var_->getPosition() + VM::vmNumReservedRegisters,
			generated);

}

}
