/*
 * Float.cpp
 *
 *  Created on: 17 Nov 2013
 *      Author: blake
 */

#include "Float.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <types.h>

namespace API {

Float32FromInt::Float32FromInt(std::string ns) :
    Function("Float", ns) {

    std::vector<ScribbleCore::TypeReference> refs;

    refs.push_back(
        ScribbleCore::makeTypeReference(
            ScribbleCore::getTypeManager().getType(ScribbleCore::Int)));

    ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
                ScribbleCore::getTypeManager().getType(ScribbleCore::Float32));

    setSignature(ScribbleCore::FunctionSignature(refs, returnType));
}

Float32FromInt::~Float32FromInt() {
}

API::APIValue Float32FromInt::execute(API::APIValue* values,
                                      VM::VirtualMachine* virt) {
    return API::APIValue(ScribbleCore::getIntType(),
                         values[0].getValueFloat32());
}

} /* namespace API */
