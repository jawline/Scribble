/*
 * GetArrayStatement.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef GETARRAYSTATEMENT_HPP_
#define GETARRAYSTATEMENT_HPP_
#include "Statement.hpp"

namespace ScribbleCore {

class GetArrayStatement: public Statement {
  private:
    SafeStatement array_;
    SafeStatement index_;
    TypeReference type_;

  public:
    GetArrayStatement(int line, std::string sym, SafeStatement array, SafeStatement index);
    virtual ~GetArrayStatement();

    TypeReference type();

    void checkTree(Type* functionType);
    int generateCode(int resultRegister, std::stringstream& generated);
    void fix();
};

}

#endif /* GETARRAYSTATEMENT_HPP_ */
