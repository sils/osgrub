#include "text_output.h"

//TODO implement kernelprintf function!!!
//dont rely on these functions

void printColoredChar(char val, const char colCode)
{
	volatile unsigned char *videoram = (unsigned char *)0xB8000;
	static u32int c=0;
	videoram[c++] = val;
	videoram[c++] = colCode;
	if(c > 80*24)
		c=0;
}

void printColoredCharPos(char val, const char colCode, u32int c)
{
	volatile unsigned char *videoram = (unsigned char *)0xB8000;
	videoram[c++] = val;
	videoram[c++] = colCode;
	if(c > 80*24)
		c=0;
}

void printColoredString(char *strPtr, const char colCode)
{
	while(*strPtr != '\0')
		{
		printColoredChar(*strPtr++, colCode);
		}
}

void printColoredStringPos(char *strPtr, const char colCode, u32int c)
{
	while(*strPtr != '\0')
		{
		printColoredCharPos(*strPtr++, colCode, c++);
		}
}

u32int strlen(char *str)
{
	u32int i=0;
	while(str[i])
		i++;
	return i;
}

void strcat(char * dest, char * append)
{
	while(*dest)
		dest++;
	while((*dest++ = *append++));
}

void strcpy(char *dest, char *src)
{
	while((*dest++ = *src++));
}

char charDigit(unsigned char val)
{
	if(val<10)
		return val+'0';
	return val-10+'A';
}

void intToStr(char *dest, s32int val, u8int base)
{
	if(val<0)
		{
		dest[0]='-';
		uIntToStr(dest+1, (u32int)(-val), base);
		}
	else uIntToStr(dest, (u32int)val, base);
}

void uIntToStr(char *dest, u32int val, u8int base)
{
	//new strategy: from the end.
	char buf[33];
	int i=32;
	buf[i]=0;
	do
		{
		buf[--i] = charDigit(val % base);
		val /= base;
		}
	while(val);
	strcpy(dest, buf+i);
}

