#ifndef MM_H
#define MM_H

#include <stdint.h>
#include <null.h>
#include <stdio.h>

struct multiBoot
{
uint32_t flags;
uint32_t memLower;
uint32_t memUpper;
uint32_t bootDevice;
uint32_t cmdLine;
uint32_t moduleCount;
void *modAdress;
uint32_t syms[4];
uint32_t mMapLength;
void *mMapAddr;
} __attribute__((packed));

struct multiBootMap
{
uint32_t entrySize;
uint64_t base;
uint64_t length;
uint32_t type;
} __attribute__((packed));

void mMInit(const struct multiBoot *);
void* mMAllocPage();
void mMFreePage(void *);
void mMPrintBitmap();
void mMPrintBitmapI(unsigned int);

extern const void kernel_start;
extern const void kernel_end;

//for 4GB memory
#define BITMAP_SIZE 32768

#endif
