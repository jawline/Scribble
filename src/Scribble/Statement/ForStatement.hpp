/*
 * ForStatement.hpp
 *
 *  Created on: 13 Mar 2013
 *      Author: blake
 */

#ifndef FORSTATEMENT_HPP_
#define FORSTATEMENT_HPP_
#include "Statement.hpp"
#include <Pointers/SmartPointer.hpp>
#include <vector>

namespace ScribbleCore {

class ForStatement: public Statement {
  private:
    SafeStatement initial_;
    SafeStatement condition_;
    SafeStatement step_;
    std::vector<SafeStatement> statements_;

  public:
    ForStatement(int lineNo, std::string sym, SafeStatement initial, SafeStatement condition, SafeStatement step, std::vector<SafeStatement> statements);
    virtual ~ForStatement();

    TypeReference type();
    void checkTree(Type* functionType);

    virtual int generateBody(std::stringstream& generated);
    virtual int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif /* FORSTATEMENT_HPP_ */
