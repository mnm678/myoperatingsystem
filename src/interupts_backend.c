#include "interupts.h"
#include "interupts_backend.h"
#include "serial.h"

uint64_t irq_c_table[256] = {
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq
};

void not_implemented_irq(void *irq) {
   printk("Unimplemented interupt %x", (uint64_t) irq);
   while(1){};
}

void irq_c_handler(int irq, int err) {
   /*printk("irq_c_handler\n");
   while(1){};*/
   ((void (*)(void*))irq_c_table[irq])((void *)irq);
}
