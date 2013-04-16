#include "kernel/include.h"

void init(void)
{
	extern uint32_t magic;
	if ( magic != 0x2BADB002 )
	{
		printString("There was an error during the boot sequence! (Magic number does not match.)");
	}

	printString("Kernel booted.");
	gdt_install();
	printString("Sucessfully installed global descriptor table!");
	generateIdt();
	printString("Sucessfully installed interupt descriptor table!");
	
	//for testing
	printString("Triggering interrupt no 3:");
	asm volatile ("int $0x3");
	printString("Divide by zero now...");
	asm volatile ("int $0x2A"); // trigger irq event no 42
	printString("Initialize timer now...");
	initTimer(100);
	// int g=0;
	//asm volatile("int $0x0");
	 //g=5/g;// SOMEHOW this exception doesn't work that well
	// it is triggered on and on...
	printString("Sucessfully divided 5 by zero :)");
	asm volatile ("int $0x20");

	for(;;);
}
