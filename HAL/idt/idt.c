#include "idt.h"

void setIdtEntry(unsigned char id, unsigned long base, unsigned short sel, unsigned char flags)
{
	idt[id].base_lo = (base & 0xFFFF);
	idt[id].sel = sel;
	idt[id].always0 = 0;
	// when in user mode CHANGE PRIVILEGE LEVEL!!!
	idt[id].flags = flags;
	idt[id].base_hi = ((base>>16) & 0xFFFF);
}

void remapIrq()
{
	//send commands to PIC
	outb(0x20, 0x11); //initialize master PIC
	outb(0x21, 0x20);
	outb(0x21, 0x04);
	outb(0x21, 0x01);
	
	outb(0xA0, 0x11); //initialize slave PIC
	outb(0xA1, 0x28);
	outb(0xA1, 0x02);
	outb(0xA1, 0x01);
	
	//activate IRQs
	outb(0x20,0x0);
	outb(0xA0, 0x0);
	//outb(0x21, 0x0);
	//outb(0xA1, 0x0);
}

void generateIdt()
{
	idtp.limit = (sizeof(struct idt_entry) * IDT_ENTRIES) -1;
	idtp.base = (unsigned int)&idt;
	
	// initialize IDT with zeroes
	memset((unsigned char *)&idt, 0, sizeof(struct idt_entry)*IDT_ENTRIES);
	
	remapIrq();
	
	// define IDT entries here
	setIdtEntry(0 , (unsigned int)isr0 , 0x08, 0x8e);
	setIdtEntry(1 , (unsigned int)isr1 , 0x08, 0x8e);
	setIdtEntry(2 , (unsigned int)isr2 , 0x08, 0x8e);
	setIdtEntry(3 , (unsigned int)isr3 , 0x08, 0x8e);
	setIdtEntry(4 , (unsigned int)isr4 , 0x08, 0x8e);
	setIdtEntry(5 , (unsigned int)isr5 , 0x08, 0x8e);
	setIdtEntry(6 , (unsigned int)isr6 , 0x08, 0x8e);
	setIdtEntry(7 , (unsigned int)isr7 , 0x08, 0x8e);
	setIdtEntry(8 , (unsigned int)isr8 , 0x08, 0x8e);
	setIdtEntry(9 , (unsigned int)isr9 , 0x08, 0x8e);
	setIdtEntry(10, (unsigned int)isr10, 0x08, 0x8e);
	setIdtEntry(11, (unsigned int)isr11, 0x08, 0x8e);
	setIdtEntry(12, (unsigned int)isr12, 0x08, 0x8e);
	setIdtEntry(13, (unsigned int)isr13, 0x08, 0x8e);
	setIdtEntry(14, (unsigned int)isr14, 0x08, 0x8e);
	setIdtEntry(15, (unsigned int)isr15, 0x08, 0x8e);
	setIdtEntry(16, (unsigned int)isr16, 0x08, 0x8e);
	setIdtEntry(17, (unsigned int)isr17, 0x08, 0x8e);
	setIdtEntry(18, (unsigned int)isr18, 0x08, 0x8e);
	setIdtEntry(19, (unsigned int)isr19, 0x08, 0x8e);
	setIdtEntry(20, (unsigned int)isr20, 0x08, 0x8e);
	setIdtEntry(21, (unsigned int)isr21, 0x08, 0x8e);
	setIdtEntry(22, (unsigned int)isr22, 0x08, 0x8e);
	setIdtEntry(23, (unsigned int)isr23, 0x08, 0x8e);
	setIdtEntry(24, (unsigned int)isr24, 0x08, 0x8e);
	setIdtEntry(25, (unsigned int)isr25, 0x08, 0x8e);
	setIdtEntry(26, (unsigned int)isr26, 0x08, 0x8e);
	setIdtEntry(27, (unsigned int)isr27, 0x08, 0x8e);
	setIdtEntry(28, (unsigned int)isr28, 0x08, 0x8e);
	setIdtEntry(29, (unsigned int)isr29, 0x08, 0x8e);
	setIdtEntry(30, (unsigned int)isr30, 0x08, 0x8e);
	setIdtEntry(31, (unsigned int)isr31, 0x08, 0x8e);
	
	setIdtEntry(32, (unsigned int)irq0 , 0x08, 0x8E);
	setIdtEntry(33, (unsigned int)irq1 , 0x08, 0x8E);
	setIdtEntry(34, (unsigned int)irq2 , 0x08, 0x8E);
	setIdtEntry(35, (unsigned int)irq3 , 0x08, 0x8E);
	setIdtEntry(36, (unsigned int)irq4 , 0x08, 0x8E);
	setIdtEntry(37, (unsigned int)irq5 , 0x08, 0x8E);
	setIdtEntry(38, (unsigned int)irq6 , 0x08, 0x8E);
	setIdtEntry(39, (unsigned int)irq7 , 0x08, 0x8E);
	setIdtEntry(40, (unsigned int)irq8 , 0x08, 0x8E);
	setIdtEntry(41, (unsigned int)irq9 , 0x08, 0x8E);
	setIdtEntry(42, (unsigned int)irq10, 0x08, 0x8E);
	setIdtEntry(43, (unsigned int)irq11, 0x08, 0x8E);
	setIdtEntry(44, (unsigned int)irq12, 0x08, 0x8E);
	setIdtEntry(45, (unsigned int)irq13, 0x08, 0x8E);
	setIdtEntry(46, (unsigned int)irq14, 0x08, 0x8E);
	setIdtEntry(47, (unsigned int)irq15, 0x08, 0x8E);
	
	// call assembler function
	idt_load();
	
	asm volatile("sti");
}

void register_interrupt_handler(uint16_t n, intHandler handler)
{
	interrupt_handlers[n] = handler;
}

void generalIntHandler(registers_t *regs)
{
	if(interrupt_handlers[regs->int_no])
	{
		interrupt_handlers[regs->int_no](regs);
	}
	else
	{
		kprintf("Unhandled interrupt (%d)\n", regs->int_no);
		//regDump(*regs);
		kernelException();
	}
	
	if (regs->int_no >= 40)
	{
		// Send reset signal to slave.
		outb(0xA0, 0x20);
	}
	if(regs->int_no >= IRQ0)
		outb(0x20, 0x20);//reset signal to master PIC
}