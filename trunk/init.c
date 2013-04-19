#include "kernel/include.h"

void init(void)
{
	print("Kernel booted HOPEFULLY from stick.\n");
	gdt_install();
	initTimer(100);
	register_interrupt_handler(IRQ1, &keyboardHandler);
	generateIdt();
	kprintf("Everything's set up. You can start typing now and see what happens (uuuuh it appears!)\n");

	for(;;);
}
