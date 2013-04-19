CC	= gcc
CFLAGS	= -m32 -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -ffreestanding
LD	= ld
LDFLAGS = -melf_i386 -T linker.ld
 
SRCS = $(shell find -name '*.[csS]')
OBJFILES = $(addsuffix .o,$(basename $(SRCS)))
 
default: kernel.bin

all: clean kernel.bin

.s.o:
	nasm -f elf -o $@ $<
 
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
 
kernel.bin: $(OBJFILES)
	$(LD) $(LDFLAGS) -o $@ $^
 
iso: kernel.bin
	cp kernel.bin buildhelpers/iso/boot/kernel
	echo "Creating grub iso."
	grub-mkrescue -o buildhelpers/bootable.iso buildhelpers/iso
	echo "Just dd the ISO to your stick!"
 
clean:
	$(RM) $(OBJFILES) kernel.bin kernel.img *~ */*~ */*/*~ */*/*/*~ kernel.o floppy.img buildhelpers/pad buildhelpers/grubiso/boot/grub/kernel
