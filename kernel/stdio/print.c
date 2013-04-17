#include "print.h"

void put(const unsigned char val, const u8int color)
{
	static u8int x=0, y=0;
	u16int i;
	volatile unsigned char *videoram = (unsigned char *)0xB8000;
	
	if(val == '\n')
		{
		x=0;
		y++;
		return;
		}
	
	if(x>79)
		{
		x=0;
		y++;
		}
	if(y>24)//scroll up one line
		{
		for(i=0;i<24*80*2;i++)
			videoram[i]=videoram[i+160];
		for(; i<2*25*80;i++)
			{
			if(i % 2)
				videoram[i]=0;
			else videoram[i]=' ';
			}
		y--;
		}
	
	videoram[2*(y*80 + x)] = val;
	videoram[2*(y*80 + x)+1] = color;
	x++;
}

void print(char *str)
{
	while(*str)
		putChar(*str++);
}

char charDigit(const unsigned char val)
{
	if(val<10)
		return val+'0';
	return val-10+'A';
}

void intToStr(char *dest, const s32int val, const u8int base)
{
	if(val<0)
		{
		*(dest)='-';
		uIntToStr(dest+1, (u32int)(-val), base);
		}
	else uIntToStr(dest, (u32int)val, base);
}

void uIntToStr(char *dest, u32int val, const u8int base)
{
	//at binary representation we can have max 32 digits
	char buf[33];
	u8int i=32;
	buf[i]=0;
	do
		{
		buf[--i] = charDigit(val % base);
		val /= base;
		}
	while(val);
	strcpy(dest, buf+i);
}

void kprintf(const char *format, ...)
{
	u32int u_32_int;
	char *strPtr, numStr[6];
	va_list args;
	va_start(args, format);
	
	while(*format)
		{
		if(*format == '%')
			{
			switch (*(++format))
				{
				case 's'://string
					strPtr = va_arg(args, char *);
					print(strPtr);
					break;
				case 'u'://unsigned integer
					u_32_int = va_arg(args, u32int);
					uIntToStr(numStr, u_32_int, 10);
					print(numStr);
					break;
				case 'x'://hexadecimal unsigned integer
					u_32_int = va_arg(args, u32int);
					uIntToStr(numStr, u_32_int, 16);
					print("0x");
					print(numStr);
					break;
				case '%':
					putChar('%');
					break;
				default://unrecognized
					putChar('%');
					putChar(*format);
					break;
				}
			}
		else
			{
			putChar(*format);
			}
		format++;
		}
	
	va_end(args);
}
