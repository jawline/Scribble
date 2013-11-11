/*
 * VirtualMachine_Macros.hpp
 *
 *  Created on: 24 Oct 2013
 *      Author: blake
 */

#ifndef VIRTUALMACHINE_MACROS_HPP_
#define VIRTUALMACHINE_MACROS_HPP_
#include "Constants.hpp"
#include <stdio.h>

#define VM_PRINTF_FATAL(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__); VM_PRINTF_LOG(fmt, __VA_ARGS__); this->printState(); do { } while (1)

#ifdef VM_DEBUG
extern FILE* flog;
#endif

#if VM_DEBUG == 3
#define VM_PRINTF_DBG(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#define VM_PRINTF_WARN(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#define VM_PRINTF_LOG(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#elif VM_DEBUG == 2
#define VM_PRINTF_DBG(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#define VM_PRINTF_WARN(fmt, ...) fprintf(flog, fmt, __VA_ARGS__); fflush(flog)
#define VM_PRINTF_LOG(fmt, ...)
#elif VM_DEBUG == 1
#define VM_PRINTF_DBG(fmt, ...)
#define VM_PRINTF_WARN(fmt, ...) fprintf(flog, fmt, __VA_ARGS__) fflush(flog);
#define VM_PRINTF_LOG(fmt, ...)
#else
#define VM_PRINTF_WARN(fmt, ...)
#define VM_PRINTF_DBG(fmt, ...)
#define VM_PRINTF_LOG(fmt, ...)
#endif

#endif /* VIRTUALMACHINE_MACROS_HPP_ */
