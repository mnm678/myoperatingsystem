#include "interupts.h"
#include "interupts_backend.h"
#include "serial.h"
#include "idt_setup.h"
#include "PS2.h"

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
(uint64_t) keyboard_interrupt,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) serial_interupt,
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
   int k = 1;
   printk("Unimplemented interupt %x", (uint64_t) irq);
   while(k){};
}

void keyboard_interrupt(void *irq) {
   int k = 1;
   /*printk("keyboard interrupt\n");*/

   /*while(k) {};*/
   /*read from buffer*/
   read_and_print();

   IRQ_end_of_interupt((int)irq - 0x20);
}

void irq_c_handler(int irq, int err) {
   /*printk("irq_c_handler\n");
   while(1){};*/
   ((void (*)(void*))irq_c_table[irq])((void *)irq);
}