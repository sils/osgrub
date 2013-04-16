#ifndef print_h
#define print_h

#include "stdio.h"

void kprintf(const char *, ...);
void put(const unsigned char, const u8int);
void print(char *);
char charDigit(const unsigned char);
void uIntToStr(char *, u32int, const u8int);
void intToStr(char *, const s32int, const u8int);

#define putChar(toput) put((toput), 0x0f)

#endif
