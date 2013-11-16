/*
 * VirtualMachine_Debug.cpp
 *
 *  Created on: 24 Oct 2013
 *      Author: blake
 */

#include "VirtualMachine_Debug.hpp"

#ifdef VM_DEBUG

/**
 * If a debug flag is set then open the log file for writing. Used by the VM_PRINTF_X macros
 */

FILE* flog = fopen("VMLogFile", "w");

#endif
