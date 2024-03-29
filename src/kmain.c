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
#include "block_device.h"
#include "ata_driver.h"
#include "vfs.h"
#include "fat32.h"
#include "sys_calls.h"

void user_start() {
   char c;
   putc('h');
   c = getc();
   putc(c);
   kexit();
}

void ata_test(void *arg) {
   uint8_t *buff;
   int k=1;

   ATABlockDev *drive = ata_init();
   SuperBlock sb;
   void *arg_sb;

   /*buff = kmalloc(512 * sizeof(char));
   ata_read_block((BlockDev*)drive, 0, buff);

   printk("ata: %x\n", buff[510]);*/

   sb = read_mbr(drive);

   sb.root_inode->read_dir(sb.root_inode, sb.root_inode->cb, arg_sb);

   printk("readdir test\n");
   read_test();
   printk("list all\n");
   FAT_list_all();

   kexit();
}

void halt_func(void *arg) {
   while(1) {
      asm ("hlt");
      yield();
   }
}

int kmain(uint32_t ebx) {
   void *arg = 0;
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
   BlockDev *drive;


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

   PROC_create_kthread(ata_test, arg);

   /*sys_call_test(0, 1, 5);
   sys_call_test(6, 7, 30);*/


   /*setup_snakes(1);*/

   KBD_init();
   PROC_create_kthread(KBD_input_loop, arg);
   /*PROC_create_kthread(halt_func, arg);*/

   /*PROC_create_kthread(user_start, arg);*/

   k = 1;
   while(k) {
      PROC_run();
   }

   return 0;
}
