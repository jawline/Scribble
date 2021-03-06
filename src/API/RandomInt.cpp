/*
 * RandomInt.cpp
 *
 *  Created on: 18 Mar 2013
 *      Author: blake
 */

#include "RandomInt.hpp"
#include <stdlib.h>     /* srand, rand */
#include <Scribble/Value/TypeManager.hpp>

RandomInt::RandomInt(std::string ns) :
    Function("RandomInt", ns) {

    std::vector<ScribbleCore::TypeReference> refs;

    refs.push_back(
        ScribbleCore::makeTypeReference(
            ScribbleCore::getTypeManager().getType(ScribbleCore::Int)));

    ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
                ScribbleCore::getTypeManager().getType(ScribbleCore::Int));

    setSignature(ScribbleCore::FunctionSignature(refs, returnType));
}

RandomInt::~RandomInt() {
}

APIValue RandomInt::execute(API::APIValue* values, VM::VirtualMachine* virt) {

    return API::APIValue(ScribbleCore::getIntType(),
                         rand() % values[0].getValue32());
}
