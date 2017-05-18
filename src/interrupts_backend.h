#include <stdint-gcc.h>
#include "printk.h"

void not_implemented_irq(void *, void *);
void keyboard_interrupt(void *, void *);

void irq_c_handler(uint64_t irq, uint64_t err);
void printSP();
