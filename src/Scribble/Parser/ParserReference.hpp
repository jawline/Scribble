/*
 * ParserReference.hpp
 *
 *  Created on: 15 May 2014
 *      Author: blake
 */

#ifndef PARSERREFERENCE_HPP_
#define PARSERREFERENCE_HPP_
#include <Scribble/Function/FunctionReference.hpp> // Function ref class
#include <Scribble/Statement/GetStructureElementStatement.hpp>
#include <Scribble/Statement/StructureAssignElement.hpp>

namespace ScribbleCore {

enum ParserReferenceType {
    FunctionEvaluation, Fixable
};

class ParserReference {
  private:

    ParserReferenceType type_;
    SmartPointer<FunctionReference> functionReference_;
    Statement* fixableItem_;

  public:

    ParserReference(SmartPointer<FunctionReference> reference) {
        type_ = FunctionEvaluation;
        functionReference_ = reference;
    }

    ParserReference(Statement* elementType) {
        type_ = Fixable;
        fixableItem_ = elementType;
    }

    ParserReferenceType type() {
        return type_;
    }

    SmartPointer<FunctionReference> getFunctionReference() {
        return functionReference_;
    }

    Statement* getFixable() {
        return fixableItem_;
    }

};

}

#endif /* PARSERREFERENCE_HPP_ */
