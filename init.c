#include "kernel/include.h"

void init(struct multiBoot *mbstruct)
{
	kprintf("Kernel booted successfully.\n");
	kprintf("Installing global descriptor table...\n");
	gdt_install();
	kprintf("Initiate software clock...\n");
	initTimer(100);
	kprintf("Initiate memory manager...\n");
	mMInit(mbstruct);
	kprintf("Install keyboard interrupt handler...\n");
	register_interrupt_handler(IRQ1, &keyboardHandler);
	kprintf("Install interrupt descriptor table...\n");
	generateIdt();
	initKeyboard();
	kprintf("Everything's set up. Type help to get more information.\n");
	kprintf("[user]$ ");

	for(;;);
}
