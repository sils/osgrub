#ifndef include_h
#define include_h

/*-----------------------------------\
| Includes all necessary files       |
\-----------------------------------*/

#include <stdint.h>

//input output libraries
#include "stdio/stdio.h"

//global descriptor table
#include "gdt/gdt.h"

//everything for memory management
#include "memory/memory.h"

//interrupts
#include "interrupts/interrupts.h"
//#include "extern/isrs.c"

//exception handling
#include "exceptions/exceptions.h"

#endif
