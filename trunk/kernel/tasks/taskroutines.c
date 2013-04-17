#include "taskroutines.h"

void task_a(void)
{
    while (1) {
        kprintf("A");
    }
}
 
void task_b(void)
{
    while (1) {
        kprintf("B");
    }
}

registers_t* init_task(uint8_t* stack, void* entry)
{
    /*\
     | CPU-Zustand fuer den neuen Task festlegen
    \*/
    registers_t new_state = {
        .eax = 0,
        .ebx = 0,
        .ecx = 0,
        .edx = 0,
        .esi = 0,
        .edi = 0,
        .ebp = 0,
        //.esp = unbenutzt (kein Ring-Wechsel)
        .eip = (uint32_t) entry,
 
        /* Ring-0-Segmentregister */
        .cs  = 0x08,
        //.ss  = unbenutzt (kein Ring-Wechsel)
 
        /* IRQs einschalten (IF = 1) */
        .eflags = 0x202,
    };
	
    registers_t* state = (void*) (stack + 4096 - sizeof(new_state));
    *state = new_state;
 
    return state;
}
