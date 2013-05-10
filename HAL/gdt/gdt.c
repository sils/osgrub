#include "gdt.h"

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

// does everything necessary to get a GDT into the memory
// and accepted by the CPU
void gdt_install()
{
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
    gp.base = (int)&gdt;

    //NULL descriptor (important!)
    gdt_set_gate(0, 0, 0, 0, 0);

    // see http://www.brokenthorn.com/Resources/OSDev12.html
	
	//kernel, code
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	//kernel, data
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	
	//user, code
	//gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	//user, data
	//gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	
	//yeah I know, it's a little general but at least they are somehow defined ;)

    // this function is defined in loader/gdtfunc.inc
    gdt_flush();
}