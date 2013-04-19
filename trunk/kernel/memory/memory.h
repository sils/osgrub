#ifndef memory_h
#define memory_h

#include "../include.h"

typedef struct allocatedMem
{
	char *startAdress;
	unsigned int count;
} allocatedMem_t;

unsigned char *memcpy(unsigned char *, const unsigned char *, u32int);
unsigned char *memset(unsigned char *, const unsigned char, u32int);

#endif
