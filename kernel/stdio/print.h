#ifndef print_h
#define print_h

#include "stdio.h"

void kprintf(char *, ...);
void put(const unsigned char, const u8int);
char charDigit(const unsigned char);
void uIntToStr(const char *, u32int, const u8int);
void intToStr(const char *, const s32int, const u8int);

#define putChar(toput) 

#endif
