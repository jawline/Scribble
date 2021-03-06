/*
* CallFunctionReference.hpp
*
*  Created on: 5 Jun 2014
*      Author: blake
*/

#ifndef CALLFUNCTIONREFERENCE_HPP_
#define CALLFUNCTIONREFERENCE_HPP_
#include "Statement.hpp"
#include <Pointers/SmartPointer.hpp>
#include <API/Function.hpp>
#include <Scribble/Function/FunctionReference.hpp>
#include <VM/Constants.hpp>
#include <stdio.h>
#include <vector>

namespace ScribbleCore {

class CallFunctionReference: public Statement {
  private:
	int numDeclaredVariables_;
    SafeStatement fn_;
    std::vector<SafeStatement> args_;
    TypeReference returnType_;

  public:
    CallFunctionReference(int lineNo, std::string sym, SafeStatement fn,
                          std::vector<SafeStatement> args, int numDeclaredVariables);
    virtual ~CallFunctionReference();

    virtual void checkTree(Type* functionType);

    /**
     * AndStatements type is boolean.
     */

    virtual TypeReference type();

    int generateCode(int resultRegister, std::stringstream& generated);
    void fix();
};

} /* namespace ScribbleCore */
#endif /* CALLFUNCTIONREFERENCE_HPP_ */
