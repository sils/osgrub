#include "tasks.h"

//taskStates is of type task*

void initMultitasking()
{
	taskStates = mMAllocPage();
	taskStates[0]=(task *)NULL;
	taskCount = 0;
	kprintf("Multitasking was successfully initialized.\n");
}

//TODO DEBUG
void* initTask(void * entry)
{
	static unsigned short ids = 0;
	task *dest=0;
	
	kprintf("Entry point: %x\n",(uint32_t) entry);
	dest = mMAllocPage();
	
	taskStates[ids]= (void*)dest+0x1000-sizeof(task);
	registers_t new_state =
	{
		.eax = 0,
		.ebx = 0,
		.ecx = 0,
		.edx = 0,
		.esi = 0,
		.edi = 0,
		.ebp = 0,
		//.esp = unused - we stay in ring 0 for now
		.eip = (uint32_t) entry,
		
		.cs  = 0x08,
		//.ss unused for now
		
		//interrupt flag on
		.eflags = 0x202,
	};
	task newtask = {
		.taskId = ids++,
		.regs = new_state,
		.status = 0,
		.timeFact = 1,
		.userId = 0, //I AM ROOT
		.prevQueue = NULL,
		.nextQueue = NULL,
		.mem = NULL, //save dest here as one entry too???
	};
	kprintf("Newtask: %x",newtask.regs.eip);
	
	
	(*taskStates[ids]).taskId = ids++;
	(*taskStates[ids]).regs = new_state;
	kprintf("Addr: %x\nEntry point IS: %x\n",(*taskStates[ids]).taskId);
	
	taskCount++;
	return dest;
}