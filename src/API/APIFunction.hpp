/*
 * APIFunction.hpp
 *
 *  Created on: 6 Jan 2014
 *      Author: blake
 */

#ifndef APIFUNCTION_HPP_
#define APIFUNCTION_HPP_
#include <vector>
#include <API/Function.hpp>
#include <API/Value/APIValue.hpp>
#include <Scribble/Value/Type.hpp>

namespace API {

/**
 * The APIFunction class can be used to register a function pointer instead of a Function wrapper class.
 */

class APIFunction: public Function {
  private:
    ScribbleCore::Type* returnType_;
    std::vector<ScribbleCore::Type*> types_;
    API::APIValue (*fn_)(API::APIValue*, VM::VirtualMachine* virt);

  public:

    APIFunction(std::string name, std::string package, ScribbleCore::FunctionSignature signature,
                API::APIValue (*fn)(API::APIValue*, VM::VirtualMachine* virt));

    virtual ~APIFunction();

    APIValue execute(API::APIValue* values, VM::VirtualMachine* virt);
};

} /* namespace API */
#endif /* APIFUNCTION_HPP_ */
