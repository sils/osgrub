#ifndef kshell_h
#define kshell_h

void shInterpret(char *);
void shDate();
void shHelp();
void shAlloc();
void shFree(char*);
void shMemInfo();
void shPrintBitmap();

#include <stdio.h>
#include <null.h>
#include "../interrupts/timer/timer.h"
#include <memory.h>
#include "../tasks/taskroutines.h"
#include "../tasks/tasks.h"

#endif
