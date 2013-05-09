#include "memory.h"

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, uint32_t count)
{
	uint32_t i;
	for(i=0;i<count;i++)
		dest[i]=src[i];
	return dest;
}

unsigned char *memset(unsigned char *dest, const unsigned char val, uint32_t count)
{
	uint32_t i;
	for(i=0;i<count;i++)
		dest[i]=val;
	return dest;
}
