#include "exceptions.h"

void printException(char *message)
{
	printColoredString(message, 0x0c);
}

void printFatalException(char *message)
{
	printColoredString(message, 0x04);
	printColoredString(" HALTING SYSTEM!", 0x04);
	kernelException(); //yeah this is not that great
	// just prevents the system from doing anything
}
