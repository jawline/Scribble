/*
 * Pow.hpp
 *
 *  Created on: 21 Nov 2013
 *      Author: blake
 */

#ifndef POW_HPP_
#define POW_HPP_
#include "Function.hpp"

namespace API {

class Pow: public Function {
  private:
    std::string namespace_;

  public:
    Pow(std::string ns);
    virtual ~Pow();

    /**
     * Returns the resulting modulo as an API value.
     */

    virtual APIValue execute(API::APIValue* values, VM::VirtualMachine* virt);

};

class PowFloat32: public Function {
  private:
    std::string namespace_;

  public:
    PowFloat32(std::string ns);
    virtual ~PowFloat32();

    /**
     * Returns the resulting modulo as an API value.
     */

    virtual APIValue execute(API::APIValue* values, VM::VirtualMachine* virt);

};

} /* namespace API */
#endif /* POW_HPP_ */
