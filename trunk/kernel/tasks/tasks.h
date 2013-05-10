#ifndef TASKS_H
#define TASKS_H

#include <regs.h>
#include <null.h>
#include <stdint.h>

#include "../memory/mm.h"
#include "../interrupts/scheduler.h"

void* initTask(uint32_t);
void initMultitasking();

uint8_t taskCount;

#endif
