#ifndef _VM_CONSTANTS_DEF_H_
#define _VM_CONSTANTS_DEF_H_

#include "ConstantRegisters.hpp"
#include "ConstantTypes.hpp"
#include "CallTypes.hpp"

namespace VM {

const static unsigned int vmOpCodeSize = 8;
const static unsigned int GarbageCollectHitLimit = 50;
const static unsigned int vmTrue = 1;
const static unsigned int vmFalse = 0;

}

#endif //_VM_CONSTANTS_DEF_H_
