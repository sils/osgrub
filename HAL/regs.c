#include "regs.h"

/*
 * typedef struct registers
 * {
 * uint32_t ds;                  // Data segment selector
 * uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
 * uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
 * uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
 * } registers_t;
 */

void regDump(registers_t regs)
{
	kprintf("Register dump:\n");
	kprintf("   ds : %x\n",regs.ds);
	kprintf("   edi: %x\n",regs.edi);
	kprintf("   esi: %x\n",regs.esi);
	kprintf("   ebp: %x\n",regs.ebp);
	kprintf("   esp: %x\n",regs.esp);
	kprintf("   ebx: %x\n",regs.ebx);
	kprintf("   edx: %x\n",regs.edx);
	kprintf("   ecx: %x\n",regs.ecx);
	kprintf("   eax: %x\n",regs.eax);
	kprintf("   eip: %x\n",regs.eip);
	kprintf("   cs : %x\n",regs.cs);
	kprintf("   efl: %x\n",regs.eflags);
	kprintf("   ues: %x\n",regs.useresp);
	kprintf("   ss : %x\n",regs.ss);
	
	kprintf("   int_no: %x\n",regs.int_no);
	kprintf("   err_code: %x\n",regs.err_code);
}