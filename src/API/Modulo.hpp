/*
 * Modulo.hpp
 *
 *  Created on: May 18, 2013
 *      Author: blake
 */

#ifndef MODULO_HPP_
#define MODULO_HPP_
#include "Function.hpp"

/**
 * Built in function which provides modulo functionality (The remainder of division) so Mod(5,3) = 2
 */

class Modulo: public Function {
  private:
    std::string namespace_;

  public:
    Modulo(std::string namesp);
    virtual ~Modulo();

    /**
     * Returns the resulting modulo as an API value.
     */
    virtual APIValue execute(API::APIValue* values, VM::VirtualMachine* virt);
};

#endif /* MODULO_HPP_ */
