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

char strcmp(char *str1, char *str2)
{
	while((*str1 == *str2) && *str1 && str2)
	{
		str1++;
		str2++;
	}
	if(*str1 == *str2)
		return 1;
	return 0;
}
