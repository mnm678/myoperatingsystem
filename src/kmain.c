#include "VGA_Driver.h"
#include "PS2.h"
#include "printk.h"

int kmain() {
   VGA_clear();
   VGA_display_str("Test\n");

   printk("hello\n");
   printk("%d\n", 4);
   printk("%d\n", -54921);
   printk("%u\n", 45);
   printk("%u\n", -45);
   printk("%x\n", 5);
   printk("%x\n", 12);
   printk("%x\n", 17);
   printk("hello\n");

   initialize_ps2();
   initialize_keyboard();

   while(1) {
      read_and_print();
      
   }

}
