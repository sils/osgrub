#ifndef TASKS_H
#define TASKS_H

#include <idt/idt.h>

struct taskstruct
{
	unsigned short taskId;
	struct registers regs;
	unsigned char status;
	unsigned char timeFact;
	unsigned char userId;
	struct task * prevQueue;
	struct task * nextQueue;
	struct allocatedMem *mem;
} __attribute__((packed));

typedef struct taskstruct task;

#endif
