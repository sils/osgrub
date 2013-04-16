#include "kernel/include.h"

void init(void)
{
	extern uint32_t magic;
	if ( magic != 0x2BADB002 )
	{
		print("There was an error during the boot sequence! (Magic number does not match.)");
	}

	print("Kernel booted.\n");
	gdt_install();
	print("Sucessfully installed global descriptor table!\n");
	
	print("Sucessfully installed interupt descriptor table!\n");
	
	initTimer(100);
	generateIdt();
	// int g=0;
	//asm volatile("int $0x0");
	 //g=5/g;// SOMEHOW this exception doesn't work that well
	// it is triggered on and on...
	print("Sucessfully divided 5 by zero :)\n");
	asm volatile ("int $0x20");

	for(;;);
}
