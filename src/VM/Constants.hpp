#ifndef _VM_CONSTANTS_DEF_H_
#define _VM_CONSTANTS_DEF_H_

#include "ConstantRegisters.hpp"
#include "ConstantTypes.hpp"
#include "CallTypes.hpp"

/**
 * VM Debug level. Changes the amount of output produced by VMLogFile
 * TODO: Document what it changes.
 */

#define VM_DEBUG 3

namespace VM {

const static unsigned int vmOpCodeSize = 8;
const static unsigned int GarbageCollectHitLimit = 50;
const static unsigned int vmTrue = 1;
const static unsigned int vmFalse = 0;

/**
 * The size of each stack block in bytes
 */

const static unsigned int vmStackBlockSize = 1024;

/**
 * The amount to increment the stack by if it is expanded in stack blocks
 */

const static unsigned int vmStackIncrement = 32;

/**
 * The size in bytes of a stack increase
 */

const static unsigned int vmStackIncrease = vmStackBlockSize * vmStackIncrement;

const static char vmNamespaceSeperator = ':';

}

#endif //_VM_CONSTANTS_DEF_H_
