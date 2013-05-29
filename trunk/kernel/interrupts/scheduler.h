#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <regs.h>

task** taskStates;

void schedule(registers_t *);

#include "../tasks/tasks.h"

#endif