ENTRY (loader)

SECTIONS
{
    . = 0x100000;
    
    kernel_start = .;

    .text ALIGN (0x1000) :
    {
    	*(.multiboot)
        *(.text)
    }

    .rodata ALIGN (0x1000) :
    {
        *(.rodata*)
    }

    .data ALIGN (0x1000) :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
    
    . = ALIGN(0x1000);
    kernel_end = .;
}
