#ifndef include_h
#define include_h

/*-----------------------------------\
| Includes all necessary files       |
\-----------------------------------*/

//standard integer datatypes
#include <stdint.h>

//NULL
#include <null.h>

//for accessing unnamed parameters in printf and so on
#include <stdarg.h>

//input output libraries
#include "stdio/stdio.h"

//global descriptor table
#include <gdt/gdt.h>

//everything for memory management
#include "memory/memory.h"

//everything about interrupts
#include "interrupts/interrupts.h"

//exception handling
#include "exceptions/exceptions.h"

//access to some BIOS information from HAL
#include <CMOS/cmos.h>

//our kernel-shell
#include "kshell/kshell.h"

//let's start multitasking!
#include "tasks/taskroutines.h"
#include "tasks/tasks.h"

#endif
