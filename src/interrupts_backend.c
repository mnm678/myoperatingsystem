#include "interrupts.h"
#include "interrupts_backend.h"
#include "serial.h"
#include "idt_setup.h"
#include "PS2.h"
#include "virtual_allocation.h"
#include "sys_calls.h"

void printSP() {
   register int sp asm("sp");
   printk("%x\n", sp);
}

uint64_t getCR2() {
   uint64_t CR2;
   asm("mov %%cr2, %0;" : "=r" ( CR2 ));
   return CR2;
}
   

void tss_test(void *irq, void *err) {
   int k = 1;
   while(k){};
   printSP();
}

void page_fault_handler(uint64_t irq, uint64_t err) {
   pt_entry *l1;
   union virt j;
   int k=1;

   printk("page fault\n");
   /*while(k){};*/

   j.i = getCR2();

   l1 = setup_pt(j.va, getCR3());

   if (l1[j.va.l1_ndx].avl && !l1[j.va.l1_ndx].p){
      l1[j.va.l1_ndx].base_addr = (uint64_t)MMU_pf_alloc() >>12;
      l1[j.va.l1_ndx].p = 1;
   }
   else {
      printk("page fault on %x with cr3 %x and error %x\n", j.i, getCR3(), err);
   }

}

void sys_call_handler(uint64_t irq, uint64_t err, uint64_t sys_call_num) {
   printk("here: %d\n", sys_call_num);
   if (sys_call_num >= 30) {
      printk("invalid sys call\n");
   }
   else {
      ((sys_call_func)sys_impl[sys_call_num])();
   }

}

uint64_t irq_c_table[256] = {
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) tss_test,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) page_fault_handler,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
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
(uint64_t) serial_interrupt,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) sys_call_handler, /*0x80*/
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
(uint64_t) not_implemented_irq,
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

void not_implemented_irq(void *irq, void *err) {
   int k = 1;

   printk("Unimplemented interrupt %lx: %lx", (uint64_t) irq, (uint64_t) err);
   /*while(k){};*/
}

void keyboard_interrupt(void *irq, void *err) {
   int k = 1;
   /*printk("keyboard interrupt\n");*/

   /*while(k) {};*/
   /*read from buffer*/
   read_and_print();

   IRQ_end_of_interrupt((uint64_t)irq - 0x20);
}

void irq_c_handler(uint64_t irq, uint64_t err, uint64_t save) {
   /*printk("irq_c_handler\n");
   while(1){};*/
   ((void (*)(void *,void*, void*))irq_c_table[irq])((void *)irq, (void *) err, save);
}

