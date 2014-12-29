/*
 * ArrayStatement.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef ARRAYSTATEMENT_HPP_
#define ARRAYSTATEMENT_HPP_
#include "Statement.hpp"

namespace ScribbleCore {

/**
 * ArrayStatement which returns a new Array of length returned by the supplied statement.
 */

class ArrayStatement: public Statement {
  private:

    /**
     * The type of array being generated.
     */

    TypeReference type_;

    /**
     * Statement which returns the length of the new array.
     */

    SafeStatement length_;

  public:

    /**
     * Construct array statement.
     * @param line The line number.
     * @param text The symbol it occurs at.
     * @param type The type of array to be generated.
     * @param length The statement which returns the length.
     */

    ArrayStatement(int line, std::string text, TypeReference type, SafeStatement length);
    virtual ~ArrayStatement();

    /**
     * Returns Array type.
     * @return Array.
     */

    TypeReference type();

    void checkTree(Type* functionType);
    int generateCode(int resultRegister, std::stringstream& generated);
};

}

#endif /* ARRAYSTATEMENT_HPP_ */
