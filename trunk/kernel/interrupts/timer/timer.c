#include "timer.h"

u32int tick = 0, freq, sec=0;

static void timerInterrupt(registers_t regs)
{
	tick++;
	if(tick % freq == 0)
		{
		sec++;
		}
}

void initTimer(const u32int frequency)
{
	freq = frequency;
	
	register_interrupt_handler(IRQ0, &timerInterrupt);
	u32int divisor = 1193180 / frequency;
	
	outb(0x43, 0x36);
	
	u8int l = (u8int)(divisor & 0xFF);
	u8int h = (u8int)( (divisor>>8) & 0xFF );
	
	outb(0x40, l);
	outb(0x40, h);
}
