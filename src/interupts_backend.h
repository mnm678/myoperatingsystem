#include <stdint-gcc.h>
#include "printk.h"

void not_implemented_irq(void *);
void keyboard_interrupt(void *);

void irq_c_handler(int irq, int err);
