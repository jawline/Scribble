#include "GetVariableStatement.hpp"
#include <VM/Constants.hpp>

namespace ScribbleCore {

GetVariableStatement::GetVariableStatement(int lineNo, std::string sym,
		SmartPointer<Variable> var) :
		Statement(lineNo, sym) {
			var_ = var;
		}

GetVariableStatement::~GetVariableStatement() {
}

Type* GetVariableStatement::type() {
	return var_->getType();
}

void GetVariableStatement::checkTree(Type* functionType) {

	if (var_->getType()->getType() == TypeUnresolved) {
		throw StatementException(this, "Variable type has not been resolved.");
	}

}

int GetVariableStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	//If the result register is -1 ( The result is to be discarded ) then do not move. If the statement is something like j := j; then don't generate the move.
	if (resultRegister != -1
			|| resultRegister
					!= (int) (var_->getPosition() + VM::vmNumReservedRegisters)) {

		generated << "move $"
				<< (var_->getPosition() + VM::vmNumReservedRegisters) << " $"
				<< resultRegister << "\n";

		return 1;
	}

	return 0;
}

}
