#include "VGA_Driver.h"
#include "PS2.h"
#include "printk.h"
#include "idt_setup.h"
#include "interupts.h"
#include "serial.h"
#include <limits.h>

int kmain() {
   int test = 1;
   short test_short = 2;
   unsigned short test_ushort = 100;
   unsigned long test_ulong = 3000000000;
   long test_long = -40000000000;
   int k=0;
   while(k) {
   };

   /*set up interupts*/
   PIC_setup();
   idt_setup();
   IRQ_set_all_masks();
   IRQ_clear_mask(1);
   VGA_clear();
   /*serial_setup();*/

   /*while(1) {
      printk("%d\n",pic_get_irr());
      printk("%d\n",pic_get_isr());
   }*/

   STI();
   /*serial_write_char('a');
   serial_write_char('\n');
   serial_write_char('a');
   serial_write_char('\n');
   serial_write("hello, world\n", 13);*/
   /*irq20_handler();*/

   printk("hello\n");
   printk("%d\n", 4);
   printk("%d\n", -54921);
   printk("%u\n", 45);
   printk("%u\n", -45);
   printk("%x\n", 5);
   printk("%x\n", 12);
   printk("%x\n", 17);
   printk("50%%\n");
   printk("%c\n", 'm');
   printk("%p\n", &test);
   printk("%hd\n", test_short);
   printk("%hu\n", test_ushort);
   printk("%hx\n", test_short);
   printk("%ld\n", test_long);
   printk("%lu\n", test_ulong);
   printk("%lx\n", test_long);
   printk("%qd\n", test_long);
   printk("%qu\n", test_ulong);
   printk("%qx\n", test_long);
   printk("%s", "TEST\n");

   printk("goodbye\n");

   /*initialize_ps2();
   initialize_keyboard();*/
   /*asm("int $0x21");
   asm("int $0x21");*/

   k = 1;
   while(k) {
      /*read_and_print();*/
      
   }

}
