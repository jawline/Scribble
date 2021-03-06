/*
 * NegativeStatement.hpp
 *
 *  Created on: 29 Apr 2013
 *      Author: blake
 */

#ifndef NEGATIVESTATEMENT_HPP_
#define NEGATIVESTATEMENT_HPP_
#include "Statement.hpp"

namespace ScribbleCore {

class NegativeStatement: public Statement {
  private:
    SafeStatement exp_;

  public:
    NegativeStatement(int line, std::string text, SafeStatement exp);
    virtual ~NegativeStatement();
    virtual void checkTree(Type* functionType);
    virtual TypeReference type();


    int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif /* NEGATIVESTATEMENT_HPP_ */
