#include "../../include.h"

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

static void timerInterrupt(registers_t regs)
{
	tick++;
	if(tick % freq == 0)
	{
		if(regs.int_no != IRQ0)
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
			//if(sec == 0)
			//	kprintf("Today is: %u.%u.%u, %u:%u:%u.\n",day,mon,year,hour,min,sec);
		}
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
