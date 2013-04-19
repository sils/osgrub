#ifndef include_h
#define include_h

/*-----------------------------------\
| Includes all necessary files       |
\-----------------------------------*/

#include <stdint.h>

//general purpose macros
#include "macros.h"

//input output libraries
#include "stdio/stdio.h"

//global descriptor table
#include "gdt/gdt.h"

//everything for memory management
#include "memory/memory.h"

//everything about interrupts
#include "interrupts/interrupts.h"

//exception handling
#include "exceptions/exceptions.h"

//let's start multitasking!
#include "tasks/taskroutines.h"
#include "tasks/tasks.h"

#endif
