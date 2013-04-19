#include "strings.h"

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
