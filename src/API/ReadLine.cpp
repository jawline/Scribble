/*
 * ReadLine.cpp
 *
 *  Created on: 5 Jun 2013
 *      Author: blake
 */

#include "ReadLine.hpp"

ReadLine::ReadLine(std::string ns) :
    Function("ReadLine", ns) {

    std::vector<ScribbleCore::TypeReference> refs;

    ScribbleCore::TypeReference returnType = ScribbleCore::makeTypeReference(
                ScribbleCore::getTypeManager().getType(ScribbleCore::StringType));

    setSignature(ScribbleCore::FunctionSignature(refs, returnType));
}

ReadLine::~ReadLine() {
}

APIValue ReadLine::execute(API::APIValue* values, VM::VirtualMachine* virt) {

    std::string line;
    std::getline(std::cin, line);
    return API::APIValue::makeString(line, virt);
}
