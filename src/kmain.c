#include "VGA_Driver.h"
#include "PS2.h"
#include "printk.h"
#include <limits.h>

int kmain() {
   int test = 1;
   short test_short = 2;
   unsigned short test_ushort = 100;
   unsigned long test_ulong = 3000000000;
   long test_long = -40000000000;
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

   initialize_ps2();
   initialize_keyboard();

   while(1) {
      read_and_print();
      
   }

}
