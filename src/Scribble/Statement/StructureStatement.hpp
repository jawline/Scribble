/*
 * StructureStatement.hpp
 *
 *  Created on: 26 May 2013
 *      Author: blake
 */

#ifndef STRUCTURESTATEMENT_HPP_
#define STRUCTURESTATEMENT_HPP_
#include "Statement.hpp"
#include <Scribble/Parser/TypeReference.hpp>

namespace ScribbleCore {

class StructureStatement: public Statement {
  private:
    TypeReference type_;
    std::vector<SafeStatement> statements_;

  public:
    StructureStatement(int lineno, std::string token, TypeReference type, std::vector<SafeStatement> initials);
    virtual ~StructureStatement();

    virtual void checkTree(Type* functionType);
    virtual TypeReference type();
    virtual int generateCode(int result, std::stringstream& code);
};

}

#endif /* STRUCTURESTATEMENT_HPP_ */
