#ifndef _ASSIGN_VARIABLE_DEF_H_
#define _ASSIGN_VARIABLE_DEF_H_
#include "Statement.hpp"
#include <Scribble/Value/Variable.hpp>
#include <vector>

namespace ScribbleCore {

/**
 * Set the value of a given variable to the result of the given statement and also return it. ( So sys.Write(A := "Hello"); is valid )
 */

class AssignVariableStatement: public Statement {
private:

	/**
	 * The expression which the variable is set to the result of.
	 */
	SafeStatement exp_;

	/**
	 * The variable which is modified.
	 */

	SmartPointer<Variable> var_;

public:

	/**
	 * Construct a AssignVariableStatement.
	 * @param lineNo the line number which this occurs on.
	 * @param sym The symbol this was constructed from.
	 * @param var The variable to modify
	 * @param exp The expression which the variable is set to the result of.
	 */

	AssignVariableStatement(int lineNo, std::string sym, SmartPointer<Variable> var,
			SafeStatement exp);
	~AssignVariableStatement();

	/**
	 * Returns the type of the variable.
	 * @return The type of the variable/expression.
	 */

	Type* type() {
		return exp_->type();
	}

	void checkTree(Type* functionType);
	int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif //_ASSIGN_VARIABLE_DEF_H_
