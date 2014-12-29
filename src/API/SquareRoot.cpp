/*
 * SquareRoot.cpp
 *
 *  Created on: 6 Jan 2014
 *      Author: blake
 */

#include "SquareRoot.hpp"
#include <math.h>
#include <types.h>

APIValue SquareRootFloat32(API::APIValue* values, VM::VirtualMachine* virt) {
    return API::APIValue::makeFloat32(sqrtf(values[0].getValueFloat32()));
}
