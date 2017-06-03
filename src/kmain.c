#include "VGA_Driver.h"
#include "PS2.h"
#include "printk.h"
#include "idt_setup.h"
#include "interrupts.h"
#include "serial.h"
#include "multiboot.h"
#include <limits.h>
#include "virtual_allocation.h"
#include "kmalloc.h"
#include "keyboard_driver.h"

void sys_call_test(int unused, int unused2, int sys_call_num) {
   asm("int $0x80");
}

int kmain(uint32_t ebx) {
   void *arg;
   int test = 1;
   short test_short = 2;
   unsigned short test_ushort = 100;
   unsigned long test_ulong = 3000000000;
   long test_long = -40000000000;
   int k=1;
   void *page_frame_test;
   void *page_frame_test2;
   int i, j;
   uint64_t phy_mem_size;

   /*set up interrupts*/
   PIC_setup();
   idt_setup();
   IRQ_set_all_masks();
   IRQ_clear_mask(1);
   VGA_clear();
   serial_setup();

   phy_mem_size = findMemory(ebx);
   setup_id_map(phy_mem_size);

   STI();

   sys_call_test(0, 1, 5);
   sys_call_test(6, 7, 30);


   setup_snakes(1);

   KBD_init();
   PROC_create_kthread(KBD_input_loop, arg);

   k = 1;
   while(k) {
      PROC_run();
   }

}
