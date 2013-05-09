#ifndef memory_h
#define memory_h

#include <stdint.h>

//for the task structure
typedef struct allocatedMem
{
	char *startAdress;
	unsigned int count;
} allocatedMem_t;

unsigned char *memcpy(unsigned char *, const unsigned char *, uint32_t);
unsigned char *memset(unsigned char *, const unsigned char, uint32_t);

#include "../kernel/memory/mm.h"

#endif
