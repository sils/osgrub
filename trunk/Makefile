CC	= gcc
CFLAGS	= -m32 -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -ffreestanding
LD	= ld
LDFLAGS = -melf_i386 -T linker.ld
 
SRCS = $(shell find -name '*.[csS]')
OBJFILES = $(addsuffix .o,$(basename $(SRCS)))
 
all: kernel.img
 
.s.o:
	nasm -f elf -o $@ $<
 
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
 
kernel.bin: $(OBJFILES)
	$(LD) $(LDFLAGS) -o $@ $^
 
kernel.img: kernel.bin
	dd if=/dev/zero of=buildhelpers/pad bs=1 count=750
	cat buildhelpers/stage1 buildhelpers/stage2 buildhelpers/pad $< > $@
 
clean:
	$(RM) $(OBJFILES) kernel.bin kernel.img *~ */*~ */*/*~ */*/*/*~ kernel.o floppy.img buildhelpers/pad
 
install:
	$(RM) $(OBJFILES) kernel.bin
