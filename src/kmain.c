#include "VGA_Driver.h"
#include "PS2.h"
#include "printk.h"
#include "idt_setup.h"
#include "interupts.h"
#include "serial.h"
#include "multiboot.h"
#include <limits.h>
#include "virtual_allocation.h"
#include "kmalloc.h"

int kmain(uint32_t ebx) {
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

   /*set up interupts*/
   PIC_setup();
   idt_setup();
   IRQ_set_all_masks();
   IRQ_clear_mask(1);
   VGA_clear();
   serial_setup();

   /*while(1) {
      printk("%d\n",pic_get_irr());
      printk("%d\n",pic_get_isr());
   }*/

   phy_mem_size = findMemory(ebx);
   setup_id_map(phy_mem_size);

   STI();

   page_frame_test = MMU_alloc_page();
   printk("%x\n", page_frame_test);
   memset(page_frame_test, 'g', PAGE_SIZE);
   for (i=0; i<PAGE_SIZE; i++) {
      if (((char*)page_frame_test)[i] != 'g') {
         printk("broken\n");
      }
   }

   MMU_free_page(page_frame_test);

   page_frame_test = MMU_alloc_page();
   printk("%x\n", page_frame_test);

   page_frame_test = kmalloc(1);
   printk("%x\n", page_frame_test);

   page_frame_test = kmalloc(1);
   printk("%x\n", page_frame_test);
   
   page_frame_test = kmalloc(100);
   memset(page_frame_test, 0, 100);
   printk("%x\n", page_frame_test);

   page_frame_test = kmalloc(1);
   printk("%x\n", page_frame_test);

   kfree(page_frame_test);

   page_frame_test = kmalloc(1);
   printk("%x\n", page_frame_test);

   /*pf alloc test
   page_frame_test = MMU_pf_alloc();
   printk("%x\n", page_frame_test);

   page_frame_test2 = MMU_pf_alloc();
   printk("%p\n", page_frame_test2);

   page_frame_test = MMU_pf_alloc();
   printk("%p\n", page_frame_test);

   MMU_pf_free(page_frame_test);
   MMU_pf_free(page_frame_test2);

   page_frame_test = MMU_pf_alloc();
   printk("%p\n", page_frame_test);

   page_frame_test = MMU_pf_alloc();
   printk("%p\n", page_frame_test);*/

   /*i=0;
   while(page_frame_test != -1) {
      memset(page_frame_test, '0' + (i%74), 4096);

      for (j=0; j < 4096; j++){
         if (((char *)page_frame_test)[j] != '0'+ (i%74)) {
            printk("broken: %c\n", ((char*)page_frame_test)[j]);
         }
      }

      page_frame_test = MMU_pf_alloc();
      i++;
   }*/
   /*page_frame_test = MMU_pf_alloc();
   printk("%p\n", page_frame_test);*/
   /*memset(page_frame_test, 'g', 4096);*/

   printk("done\n");


   /*printSP();*/
   /*serial_write_char('a');
   serial_write_char('\n');
   serial_write_char('a');
   serial_write_char('\n');
   serial_write("hello, world\n", 13);*/
   /*irq20_handler();*/
   /*k=1;
   while(k){};*/
   /*printk("This is a very long string. Hopefully it is long enough.\n");

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
   printk("%ld\n", test_long);
   printk("%lu\n", test_ulong);
   printk("%lx\n", test_long);
   printk("%s", "TEST\n");

   printk("goodbye\n");*/

   /*initialize_ps2();
   initialize_keyboard();*/
   /*asm("int $0x21");*/
   k=1;
   /*while(k){};*/
   /*asm("int $0x8");
   printSP();*/

   k = 1;
   while(k) {
      /*read_and_print();*/
      
   }

}
