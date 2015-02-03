/*
 * AssignArrayStatement.hpp
 *
 *  Created on: 24 Apr 2013
 *      Author: blake
 */

#ifndef ASSIGNARRAYSTATEMENT_HPP_
#define ASSIGNARRAYSTATEMENT_HPP_
#include "Statement.hpp"

namespace ScribbleCore {

/**
 * Assigns element assign at the specified position in the given array.
 */
class AssignArrayStatement: public Statement {
  private:

    /**
     * The expression which will generate the array
     */
    SafeStatement array_;

    /**
     * The expression which generates the value to assign
     */
    SafeStatement toAssign_;

    /**
     * The expression which generates the array index
     */
    SafeStatement position_;

  public:

    /**
     * Set the array at position to the value of assign.
     */
    AssignArrayStatement(int lineno, std::string text, SafeStatement array,
                         SafeStatement assign, SafeStatement position);

    virtual ~AssignArrayStatement();

    /**
     * Returns the type of array.
     * @return array_'s type.
     */
    TypeReference type();

    void checkTree(Type* functionType);
    int generateCode(int resultRegister, std::stringstream& generated);

};

}

#endif /* ASSIGNARRAYSTATEMENT_HPP_ */
