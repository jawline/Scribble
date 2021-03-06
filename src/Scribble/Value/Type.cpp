/*
 * Type.cpp
 *
 *  Created on: 13 Apr 2013
 *      Author: blake
 */

#include "Type.hpp"
#include <Scribble/Parser/TypeReference.hpp>
#include <Scribble/Function/FunctionSignature.hpp>

namespace ScribbleCore {

Type::Type(ValueType rawType, TypeReference subType) :
    rawType_(rawType), subType_(subType) {
}

Type::Type(std::vector<TypeReference> argumentTypes, TypeReference returnType) :
    rawType_(FunctionReferenceType), referenceArgumentTypes_(argumentTypes), referenceReturnType_(
        returnType) {
}

Type::~Type() {}

bool Type::Equals(Type* other) const {

    if (other == nullptr) {
        printf("Checking type against nullptr\n");
        return false;
    }

    if (other->rawType_ != rawType_) {
        return false;
    }

    //TODO: Probably needs cleaning up. Sleepy

    //Check if the array is the same
    if (rawType_ == Array) {
        if (subType_.get() != nullptr) {
            if (other->subType_.get() == nullptr) {
                return false;
            }

            if (subType_->type() != nullptr) {

                if (other->subType_->type() == nullptr) {
                    return false;
                }

                return subType_->type()->Equals(other->subType_->type());
            }

            printf(
                "TODO: Subtypes %s %s have not been resolved. Find out why\n",
                subType_->getName().c_str(),
                other->subType_->getName().c_str());
            printf(
                "WARNING: Currently assuming structures with the same resolve name are referencing the same thing. Fix this\n");

            return subType_->getName() == other->subType_->getName();
        }
    } else if (rawType_ == FunctionReferenceType) {

        if (!referenceReturnType_->type()->Equals(
                    other->referenceReturnType_->type())) {
            return false;
        }

        if (referenceArgumentTypes_.size()
                != other->referenceArgumentTypes_.size()) {
            return false;
        }

        //TODO: This solution leads to two unresolved types being seen as different when they may be resolved
        //to the same thing (Shock, horror!) and should be corrected
        for (unsigned int i = 0; i < referenceArgumentTypes_.size(); i++) {
            if (referenceArgumentTypes_[i] != nullptr
                    && other->referenceArgumentTypes_[i]->type() != nullptr
                    && referenceArgumentTypes_[i]->type()->Equals(
                        other->referenceArgumentTypes_[i]->type())) {
            } else {
                return false;
            }
        }
    } else if (rawType_ == StructureType) {
        //Structure check is overloaded in StructureInfo
        printf("ERR SHOULD NOT BE HERE\n");
    }

    return true;
}

Type* Type::getSubtype() const {
    return subType_->type();
}

TypeReference Type::getSubtypeReference() const {
    return subType_;
}

ValueType Type::getType() const {
    return rawType_;
}

bool Type::isPrimitive() const {

    switch (rawType_) {
    case ValueType::StringType:
    case ValueType::Array:
    case ValueType::StructureType:
        return false;

    default:
        return true;
    }

}

TypeReference Type::getReferenceReturnType() const {
    return referenceReturnType_;
}

std::vector<TypeReference> Type::getReferenceArguments() const {
    return referenceArgumentTypes_;
}

std::string Type::getTypeName() const {

    switch (getType()) {

    case Array: {
        if (getSubtype() != nullptr) {
            return std::string("array(") + getSubtype()->getTypeName() + ")";
        } else {
            return "array(unresolved-type)";
        }
    }

    case FunctionReferenceType: {
        return "__fnptr";
    }

    case StructureType:
        //StructureType overrides getTypeName. This should never execute.
        return "INVALID-SHOULD-HAVE-BEEN-OVERWRITTEN";
    case ValueType::Int:
        return "int";
    case ValueType::Boolean:
        return "bool";
    case ValueType::StringType:
        return "string";
    case ValueType::Void:
        return "void";
    case ValueType::NilType:
        return "nil";
    case ValueType::Float32:
        return "float32";
    case ValueType::TypeUnresolved:
        return "unresolved-type";
    case ValueType::ValueTypeMax:
    default:
        return "invalid";
    }

}

}
