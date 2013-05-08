#ifndef CMOS_H
#define CMOS_H

#include <stdint.h>
#include <generalStdio.h>

uint8_t readSecond();
uint8_t readMinute();
uint8_t readHour();
uint8_t readDay();
uint8_t readMonth();
uint8_t readYear();

#endif
