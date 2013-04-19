#ifndef TASKS_H
#define TASKS_H

#include "../include.h"

struct task
{
	struct registers regs;
	unsigned short taskId;
	unsigned char status;
	unsigned char timeFact;
	unsigned char userId;
	struct task * prevQueue;
	struct task * nextQueue;
	struct allocatedMem *mem;
} __attribute__((packed));

typedef struct task task_t;

#endif
