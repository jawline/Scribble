/*
 * IncrementStatement.hpp
 *
 *  Created on: 27 Mar 2013
 *      Author: blake
 */

#ifndef INCREMENTSTATEMENT_HPP_
#define INCREMENTSTATEMENT_HPP_
#include "Statement.hpp"
#include <Scribble/Value/Variable.hpp>

namespace ScribbleCore {

enum IncrementType {
	Increment, Decrement
};

class IncrementStatement: public Statement {
private:
	SmartPointer<Variable> variable_;
	IncrementType operator_;
	bool post_;

public:

	IncrementStatement(int line, std::string sym, SmartPointer<Variable> var,
			IncrementType op, bool post);
	virtual ~IncrementStatement();

	virtual void checkTree(Type* functionType);
	virtual TypeReference type();
	virtual int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif /* INCREMENTSTATEMENT_HPP_ */
