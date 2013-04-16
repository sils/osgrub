#include "text_output.h"

void printColoredChar(char val, char colCode)
{
	volatile unsigned char *videoram = (unsigned char *)0xB8000;
	static uint32_t c=0;
	videoram[c++] = val;
	videoram[c++] = colCode;
	if(c > 80*24)
		c=0;
}

void printColoredString(char *strPtr, char colCode)
{
	while(*strPtr != '\0')
		{
		printColoredChar(*strPtr++, colCode);
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
	if(val==0)
		{
		dest[0]='0';
		dest[1]=0;
		return;
		}
	
	u8int i=0;
	if(val < 0)
		{
		dest[i++]='-';
		val = -val;
		}
	
	u8int helpbase=1;
	while(helpbase < val/base)
		{
		helpbase *= base;
		}
	
	char helpval;
	while(helpbase > 0)
		{
		helpval = val/helpbase;
		dest[i++]=charDigit(helpval);
		val -= helpbase*helpval;
		helpbase /= base;
		}
	dest[i]=0;
}

