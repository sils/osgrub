#ifndef timer_h
#define timer_h

#include <stdio.h>
#include <regs.h>

void initTimer(const uint32_t freq);

uint8_t sec,min,hour,day,mon;
uint16_t year;

#include <CMOS/cmos.h>
#include <null.h>
#include <idt/idt.h>
#include "../../tasks/tasks.h"

#endif
