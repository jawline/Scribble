#include "WriteFunction.hpp"
#include <stdio.h>
#include <Scribble/Value/TypeManager.hpp>

WriteFunction::WriteFunction(std::string ns) :
    Function("Write", ns) {

    std::vector<ScribbleCore::TypeReference> refs;

    refs.push_back(
        ScribbleCore::makeTypeReference(
            ScribbleCore::getTypeManager().getType(
                ScribbleCore::StringType)));

    ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
                ScribbleCore::getTypeManager().getType(ScribbleCore::Void));

    setSignature(ScribbleCore::FunctionSignature(refs, returnType));
}

API::APIValue WriteFunction::execute(API::APIValue* values,
                                     VM::VirtualMachine* virt) {
    printf("%s", (char*) values[0].getReferencePointer());
    return API::APIValue();
}
