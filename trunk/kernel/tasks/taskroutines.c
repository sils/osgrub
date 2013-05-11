#include "taskroutines.h"

void task_a(void)
{
	register unsigned int i;
	kprintf("Task A started.");
    for(;;) {
		for(i=0;i<8000000;i++);
        kprintf("A");
    }
}
 
void task_b(void)
{
	register unsigned int i;
	kprintf("Task B started.");
	for(;;) {
		for(i=0;i<8000000;i++);
        kprintf("B");
    }
}