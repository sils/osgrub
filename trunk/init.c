#include "kernel/include.h"

void init(void)
{
	extern uint32_t magic;
	if ( magic != 0x2BADB002 )
	{
		print("There was an error during the boot sequence! (Magic number does not match.)");
	}

	print("Kernel booted. :)\n");
	gdt_install();
	initTimer(100);
	register_interrupt_handler(IRQ1, &keyboardHandler);
	generateIdt();
	kprintf("Everything's set up. You can start typing now and see what happens (uuuuh it appears!)\n");

	for(;;);
}
