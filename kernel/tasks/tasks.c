#include "tasks.h"

//taskStates is of type task*

void initMultitasking()
{
	taskStates = mMAllocPage();
	if(taskStates == NULL)
	{
		kprintf("[FATAL] Failed to initialize multitasking!\n");
		//TODO trigger some exception
	}
	taskStates[0]=(task *)NULL;
	taskCount = 0;
}

void* initTask(uint32_t entry)
{
	static unsigned short ids = 0;
	task *dest=0;
	
	//kprintf("Entry point: %x\n",entry);
	dest = mMAllocPage();
	
	taskStates[ids]= dest+0x1000-sizeof(task);
	registers_t new_state =
	{
		.eax = 0,
		.ebx = 0,
		.ecx = 0,
		.edx = 0,
		.esi = 0,
		.edi = 0,
		.ebp = 0,
		.esp = (uint32_t)dest+0x1000-sizeof(task),//stack grows towards dest
		.eip = entry,
		
		.cs  = 0x08,
		.ss = 0,
		.ds = 0x10,
		
		//interrupt flag on
		.eflags = 0x246,
	};
	task newtask = {
		.taskId = ids,
		.regs = new_state,
		.status = 0,
		.timeFact = 1,
		.userId = 0, //I AM ROOT
		.prevQueue = NULL,
		.nextQueue = NULL,
		.mem = NULL, //save dest here as one entry too???
	};
	(*taskStates[ids]) = newtask;
	
	//kprintf("eip of new task: %x\n",(*taskStates[ids]).regs.eip);
	ids++;
	taskCount++;
	return dest;
}