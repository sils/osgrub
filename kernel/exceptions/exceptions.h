#ifndef exceptions_h
#define exceptions_h

#include "../stdio/print.h"


void printException(char *);
void printFatalException(char *);

extern void kernelException();

#endif
