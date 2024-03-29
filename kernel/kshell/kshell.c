#include "kshell.h"

void shInterpret(char * string)
{
	if(strcmp(string,"help"))
		shHelp();
	if(strcmp(string,"date"))
		shDate();
	if(strcmp(string,"allocPage"))
		shAlloc();
	if(strcmp(string,"memInfo"))
		shMemInfo();
	if(strcmp(string,"multitask"))
	{
		initTask((uint32_t)task_b);
		initTask((uint32_t)task_a);
		//initTask((uint32_t)task_b);
		//initTask((uint32_t)task_b);
	}
	if(string[4] == ' ')
	{
		string[4]=NULL;
		if(strcmp(string,"echo"))
			kprintf("%s\n",string+5);
	}
	if(string[7]==' ')
	{
		string[7]=NULL;
		if(strcmp(string,"memInfo"))
		{
			mMPrintBitmapI(strtoui(string+8, 16));
		}
	}
	if(string[8]==' ')
	{
		*(string+8)=NULL;
		if(strcmp(string,"freePage"))
		{
			shFree(string+9);
		}
	}
	kprintf("[user]$ ");
}

void shDate()
{
	kprintf("Today is: %u.%u.%u, %u:%u:%u.\n",day,mon,year,hour,min,sec);
}

void shMemInfo()
{
	mMPrintBitmap();
}

void shHelp()
{
	kprintf("Available commands are:\n");
	kprintf("   help\n");
	kprintf("   echo <something>\n");
	kprintf("   date\n");
	kprintf("   memInfo\n");
	kprintf("   memInfo <hexval>\n");
	kprintf("   allocPage\n");
	kprintf("   freePage <hexval>\n");
	kprintf("   multitask\n");
	kprintf("\n");
	kprintf("Please enter hexadecimal values without proceding 0x.\n");
}

void shFree(char *param)
{
	unsigned int addr;
	addr=strtoui(param,16);
	kprintf("Freeing page on adress %x.\n",addr);
	mMFreePage((void*)addr);
}

void shAlloc()
{
	kprintf("Allocating memory.\nAllocated memory is at: %x\n", (unsigned int)mMAllocPage());
}
