#include "keyboardInt.h"

void initKeyboard()
{
	while ((inb(0x64) & 0x2)); //wait until keyboard is ready
    outb(0x60,0xF4);
	register_interrupt_handler(IRQ1, &keyboardHandler);
}

void keyboardHandler(registers_t * regs)
{
	unsigned char kbd_us[128] =
	{
		0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	  '9', '0', '-', '=', '\b',	/* Backspace */
	  '\t',			/* Tab */
	  'q', 'w', 'e', 'r',	/* 19 */
	  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
		0,			/* 29   - Control */
	  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	 '\'', '\'',   1,		/* Left shift */
	 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	  'm', ',', '.', '/',   1,				/* Right shift */
	  '*',
		0,	/* Alt */
	  ' ',	/* Space bar */
		0,	/* Caps lock */
		0,	/* 59 - F1 key ... > */
		0,   0,   0,   0,   0,   0,   0,   0,
		0,	/* < ... F10 */
		0,	/* 69 - Num lock*/
		0,	/* Scroll Lock */
		0,	/* Home key */
		0,	/* Up Arrow */
		0,	/* Page Up */
	  '-',
		0,	/* Left Arrow */
		0,
		0,	/* Right Arrow */
	  '+',
		0,	/* 79 - End key*/
		0,	/* Down Arrow */
		0,	/* Page Down */
		0,	/* Insert Key */
		0,	/* Delete Key */
		0,   0,   0,
		0,	/* F11 Key */
		0,	/* F12 Key */
		0,	/* All other keys are undefined */
	};
	unsigned char kbd_us_up[128] =
	{
		0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
	  '(', ')', '_', '+', '\b',	/* Backspace */
	  '\t',			/* Tab */
	  'Q', 'W', 'E', 'R',	/* 19 */
	  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
		0,			/* 29   - Control */
	  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
	 '|', '"',   1,		/* Left shift */
	 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
	  'M', '<', '>', '?',   1,				/* Right shift */
	  '*',
		0,	/* Alt */
	  ' ',	/* Space bar */
		0,	/* Caps lock */
		0,	/* 59 - F1 key ... > */
		0,   0,   0,   0,   0,   0,   0,   0,
		0,	/* < ... F10 */
		0,	/* 69 - Num lock*/
		0,	/* Scroll Lock */
		0,	/* Home key */
		0,	/* Up Arrow */
		0,	/* Page Up */
	  '-',
		0,	/* Left Arrow */
		0,
		0,	/* Right Arrow */
	  '+',
		0,	/* 79 - End key*/
		0,	/* Down Arrow */
		0,	/* Page Down */
		0,	/* Insert Key */
		0,	/* Delete Key */
		0,   0,   0,
		0,	/* F11 Key */
		0,	/* F12 Key */
		0,	/* All other keys are undefined */
	};
	unsigned char scancode;
	static unsigned char ctrlKeys;
	static char line[80];
	static uint8_t i=0;
	
	if(regs->int_no != IRQ1)
	{
		kprintf("Wrong interrupt?\n");
		return;
	}
	scancode = inb(0x60); 
	
	if(scancode & 0x80)//a key was released
	{
		scancode &=0x7f;//set the 0x80 bit zero
		if(kbd_us[scancode] == 1)
		{
			ctrlKeys &= 0xFE;//set the last bit zero
		}
	}
	else
	{
		switch(kbd_us[scancode])
		{
			case 1:
				ctrlKeys |= 0x01;//last bit is shift status
				break;
			default:
				if(kbd_us[scancode] != '\b' || i>0)
				{
					if(ctrlKeys & 0x01)
					{
						line[i++]=kbd_us_up[scancode];
						if(kbd_us_up[scancode] == '\b')
							i-=2;
						putChar(kbd_us_up[scancode]);
					}
					else
					{
						line[i++]=kbd_us[scancode];
						if(kbd_us[scancode] == '\b')
							i-=2;
						putChar(kbd_us[scancode]);
					}
				}
				break;
		}
		if(kbd_us[scancode] == '\n')
		{
			line[--i]=NULL;
			i=0;
			shInterpret(line);
		}
	}
}
