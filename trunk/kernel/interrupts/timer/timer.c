#include "timer.h"

uint32_t tick = 0, freq;

static void refreshCmosVals()
{
	sec = readSecond();
	min = readMinute();
	hour= readHour();
	day = readDay();
	mon = readMonth();
	year= readYear()+MILLENIUM;
}

static void timerInterrupt(registers_t * regs)
{
	tick++;
	if(tick % freq == 0)
	{
		//kprintf("Sec");
		if(regs->int_no != IRQ0)
		{
			kprintf("WRONG IRQ NUMBER!\n");
		}
		else
		{
			sec++;
			if(sec == 60)
			{
				sec = 0;
				min++;
			}
			
			if(min == 60)
			{
				min = 0;
				hour++;
			}
			
			if(hour == 24)
			{
				hour = 0;
				day++;
			}
			if(day > 28)
			{
				refreshCmosVals();
			}
		}
	}
	/*
	 * typedef struct registers
	 {
	 uint32_t ds;                  // Data segment selector
	 uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
	 uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
	 uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
	 } registers_t;
	 */
	//dispatch!
	if(taskCount >0)
	{
		registers_t tmp=schedule(*regs);
		(*regs).ds = tmp.ds;
		(*regs).edi = tmp.edi;
		(*regs).esi = tmp.esi;
		(*regs).ebp = tmp.ebp;
		(*regs).esp = tmp.esp;
		(*regs).ebx = tmp.ebx;
		(*regs).ecx = tmp.ecx;
		(*regs).edx = tmp.edx;
		(*regs).eax = tmp.eax;
		(*regs).eip = tmp.eip;
		(*regs).cs = tmp.cs;
		(*regs).eflags = tmp.eflags;
		(*regs).useresp = tmp.useresp;
		(*regs).ss = tmp.ss;
	}
}

void initTimer(const uint32_t frequency)
{
	freq = frequency;
	
	register_interrupt_handler(IRQ0, &timerInterrupt);
	uint32_t divisor = 1193180 / frequency;
	
	outb(0x43, 0x36);
	
	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );
	
	outb(0x40, l);
	outb(0x40, h);
	
	refreshCmosVals();
}
