#ifndef REGS_H
#define REGS_H

#include <stdint.h>

typedef struct registers
{
	uint32_t ds;                  // Data segment selector
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
	uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
	uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

struct taskstruct
{
	unsigned short taskId;
	struct registers regs;
	unsigned char status;//TODO document what bit is doing anything
	unsigned char timeFact;//TODO what is the default value?
	unsigned char userId;//0 is kernel/root
	struct task * prevQueue;
	struct task * nextQueue;
	struct allocatedMem *mem;
} __attribute__((packed));

typedef struct taskstruct task;

void regDump(registers_t);

#include <print.h>

#endif