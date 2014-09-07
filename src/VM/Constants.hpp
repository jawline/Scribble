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

/**
 * The size of each OpCode in bytes
 */

const static unsigned int vmOpCodeSize = 8;

/**
 * The number of garbage collection 'hits' (changes to references)
 * before the garbage collector is done again
 */

const static unsigned int GarbageCollectHitLimit = 400;

/**
 * VMFalse is the value which the virtual machine identifies as false.
 */

const static unsigned int vmFalse = 0;

/**
 * vmTrue is the internal value which the VM recognizes as a true boolean
 * (While the VM recognizes anything which != vmFalse as true the BoolStatement
 * needs a concrete value when loading).
 */

const static unsigned int vmTrue = 1;

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

/**
 * The separator used to separate package from function or structure in a package name
 */

const static char vmNamespaceSeperator = ':';

}

#endif //_VM_CONSTANTS_DEF_H_
