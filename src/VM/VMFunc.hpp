/*
 * VMFunc.hpp
 *
 *  Created on: Aug 1, 2013
 *      Author: blake
 */

#ifndef VMFUNC_HPP_
#define VMFUNC_HPP_
#include <string>
#include <Pointers/SmartPointer.hpp>
#include "InstructionSet.hpp"

namespace API {
class Function;
}

using namespace API;

namespace VM {

class VMFunc {
  private:
    std::string name_;
    InstructionSet instrs_;
    SmartPointer<Function> func_;

  public:

    VMFunc() :
        name_("INVALID") {
    }

    VMFunc(std::string name, InstructionSet instrs);
    VMFunc(std::string name, SmartPointer<Function> func);
    virtual ~VMFunc();

    InstructionSet& getInstructions() {
        return instrs_;
    }

    std::string getName() {
        return name_;
    }

    SmartPointer<Function> getFunction() {
        return func_;
    }

    bool isNative();
};

} /* namespace VM */

#endif /* VMFUNC_HPP_ */
