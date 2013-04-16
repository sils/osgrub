void outb(unsigned short int port, unsigned char value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}
