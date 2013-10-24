/*
 * VirtualMachine_Debug.cpp
 *
 *  Created on: 24 Oct 2013
 *      Author: blake
 */

#include "VirtualMachine_Debug.hpp"

#ifdef VM_DEBUG
FILE* flog = fopen("VMLogFile", "w");
#endif
