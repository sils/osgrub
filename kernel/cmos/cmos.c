#include "../include.h"


uint8_t readCmos(uint8_t offset)
{
	uint8_t tmp = inb(0x70);
	outb(0x70, (tmp & 0x80) | (offset & 0x7F));
	return inb(0x71);
}

void writeCmos(uint8_t offset,uint8_t val)
{
	uint8_t tmp = inb(0x70);
	outb(0x70, (tmp & 0x80) | (offset & 0x7F));
	outb(0x71,val);
}

uint8_t bcdToInt(uint8_t bcd)
{
	return ((bcd & 0xF0)>>4)*10 + (bcd & 0x0F);
}

uint8_t readSecond()
{
	return bcdToInt(readCmos(0x00));
}

uint8_t readMinute()
{
	return bcdToInt(readCmos(0x02));
}

uint8_t readHour()
{
	return bcdToInt(readCmos(0x04));
}

uint8_t readDay()
{
	return bcdToInt(readCmos(0x07));
}

uint8_t readMonth()
{
	return bcdToInt(readCmos(0x08));
}

uint8_t readYear()
{
	return bcdToInt(readCmos(0x09));
}
