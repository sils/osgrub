#ifndef generalStdio_h
#define generalStdio_h

typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

void outb(u16int, u8int);
u8int inb(u16int);

#endif
