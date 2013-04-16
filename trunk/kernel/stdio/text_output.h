#ifndef text_output_h
#define text_output_h

#include <stdint.h>
#include "generalStdio.h"

void printColoredChar(char, const char);
void printColoredString(char *, const char);
void strcat(char *, char *);
void strcpy(char *, char *);
u32int strlen(char *);
char charDigit(unsigned char);
void intToStr(char *, s32int, u8int);

#define printChar(charVar) printColoredChar((charVar), 0x0F)
#define printString(strPtr) printColoredString((strPtr), 0x0F)

#endif
