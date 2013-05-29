#include "scheduler.h"

static int current_task = -1;

void schedule(registers_t *process)
{
	if(taskCount == 0)
		return;
	
	if(current_task >= 0)
	{
		(*taskStates[current_task]).regs = *process;
	}
	current_task++;
	current_task %= taskCount;
	
	(*taskStates[current_task]).regs.int_no = (*process).int_no;
	(*taskStates[current_task]).regs.err_code = (*process).err_code;
	
	*process = (*taskStates[current_task]).regs;
}