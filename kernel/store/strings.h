#ifndef strings_h
#define strings_h

#include "../stdio/stdio.h"

void strcat(char *, char *);
void strcpy(char *, char *);
u32int strlen(char *);
char strcmp(char *, char *);
int strtoi(char *, unsigned char);
unsigned int strtoui(char *, unsigned char);

#define upperCase(val) val-'a'+'A'
#define lowerCase(val) val-'A'+'a'

#endif
