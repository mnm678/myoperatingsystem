#ifndef KEYBOARD_DRIVER
#define KEYBOARD_DRIVER

#include "context_swap.h"
#include "PS2.h"
#define KBD_BUF_SIZE 1024


void KBD_init();

void KBD_input_loop(void *arg);

/*must be called from a blocking context*/
void KBD_read();

void kbd_isr(uint64_t irq, uint64_t err);

#endif
