#include "memory.h"

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, u32int count)
{
	u32int i;
	for(i=0;i<count;i++)
		dest[i]=src[i];
	return dest;
}

unsigned char *memset(unsigned char *dest, const unsigned char val, u32int count)
{
	u32int i;
	for(i=0;i<count;i++)
		dest[i]=val;
	return dest;
}
