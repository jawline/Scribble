/*
 * FunctionReference.hpp
 *
 *  Created on: 16 Mar 2013
 *      Author: blake
 */

#ifndef FUNCTIONREFERENCE_HPP_
#define FUNCTIONREFERENCE_HPP_
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Statement/Statement.hpp>
#include <API/Function.hpp>
#include <string>

namespace ScribbleCore {

/**
 * A function reference used by the parser to provide a link between functions and the statements that call them.
 * Without these all functions would have to be defined before they are referenced. with these however the function
 * references can be evaluated post parsing making recursion possible and forward declaration unnecessary.
 */
class FunctionReference {
  private:

    /**
     * The name of the function
     */
    std::string name_;

    /**
     * The name of the namespace the function is in.
     */
    std::string fnNamespace_;

    /**
     * Contains the issue if the function could not be resolved (like function x does not exist in the given namespace).
     */
    std::string resolveIssue_;

    std::vector<TypeReference> fnArgs_;

    /**
     * A smart pointer to the function in question, SmartPointer to nullptr if it has not been resolved.
     */
    SafeFunction func_;

    TypeReference returnType_;

  public:

    FunctionReference(std::string fnNamespace, std::string name,
                      std::vector<SafeStatement> fnArgs, SafeFunction func);

    FunctionReference(std::string fnNamespace, std::string name,
                      std::vector<TypeReference> fnArgs, SafeFunction func);

    virtual ~FunctionReference();

    std::string const& getName();
    std::string const& getNamespace();
    std::string const& getResolveIssue();

    std::string getDebugName();

    /**
     * Get the arguments to be matched against when looking for the function.
     */
    std::vector<Type*> getTargetArguments();

    std::vector<TypeReference> const& getArgTypes();

    SafeFunction getFunction();
    TypeReference getReturnType();

    void setResolveIssue(std::string issue);
    void setFunction(SafeFunction func);
};

}

#endif /* FUNCTIONREFERENCE_HPP_ */
