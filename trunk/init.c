#include "kernel/include.h"

char welcomeString[] = "_             _  _____   _        __    ___    _    _   _____   _ \n\\\\           // |  ___| | |      / _|  /   \\  | \\  / | |  ___| | |\n \\\\    _    //  | |__   | |     / /   /  _  \\ |  \\/  | | |__   | |\n  \\\\  /_\\  //   |  __|  | |     | |   | |_| | | |\\/| | |  __|  |_|\n   \\\\// \\\\//    | |___  | |___  \\ \\_  \\     / | |  | | | |___   _ \n    \\/   \\/     |_____| |_____|  \\__|  \\___/  |_|  |_| |_____| |_|\n";

void init(struct multiBoot *mbstruct)
{
	kprintf(welcomeString);
	gdt_install();
	//initialize timer with 100Hz
	initTimer(100);
	//register keyboard interrupt handler
	initKeyboard();
	//install interrupt descriptor table
	generateIdt();
	
	kprintf("IDT and GDT is set up. Keyboard should work. Date and time should be available. Memory manager is uninitialized - DONT use it!!!");
	kprintf("[user]$ ");

	for(;;);
}
