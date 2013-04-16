#include "exceptions.h"

void printException(char *message)
{
	print(message);
}

void printFatalException(char *message)
{
	print(message);
	print(" HALTING SYSTEM!");
	kernelException(); //yeah this is not that great
	// just prevents the system from doing anything
}
