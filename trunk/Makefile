CC	= gcc
CFLAGS	= -m32 -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -ffreestanding
LD	= ld
 
OBJFILES = loader.o init.o kernel/stdio/text_output.o kernel/gdt/gdt.o kernel/exceptions/exceptions.o kernel/interrupts/idt.o kernel/memory/memory.o kernel/stdio/generalStdio.o kernel/interrupts/timer/timer.o
 
all: kernel.img
 
.s.o:
	nasm -f elf -o $@ $<
 
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
 
kernel.bin: $(OBJFILES)
	$(LD) -melf_i386 -T linker.ld -o $@ $^
 
kernel.img: kernel.bin
	dd if=/dev/zero of=buildhelpers/pad bs=1 count=750
	cat buildhelpers/stage1 buildhelpers/stage2 buildhelpers/pad $< > $@
 
clean:
	$(RM) $(OBJFILES) kernel.bin kernel.img *~ */*~ */*/*~ */*/*/*~ kernel.o floppy.img buildhelpers/pad
 
install:
	$(RM) $(OBJFILES) kernel.bin
