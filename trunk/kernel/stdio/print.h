#ifndef print_h
#define print_h

#include "stdio.h"

void kprintf(const char *, ...);
void put(const unsigned char, const uint8_t);
void print(char *);
char charDigit(const unsigned char);
void uIntToStr(char *, uint32_t, const uint8_t);
void intToStr(char *, const int32_t, const uint8_t);

#define putChar(toput) put((toput), 0x0f)

#endif
