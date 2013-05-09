#ifndef keyboardInt_h
#define keyboardInt_h

#include <idt/idt.h>
#include <strings.h>
#include <stdint.h>
#include <null.h>
#include "../../kshell/kshell.h"

void keyboardHandler(registers_t *);
void initKeyboard();

#endif
