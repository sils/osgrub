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