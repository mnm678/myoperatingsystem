#include "keyboard_driver.h"

char *KBD_buff;

typedef struct kbd_struct {
   int read;
   int write;
   ProcessQueue *blocked;
} kbd_struct;

kbd_struct *kbd;

void KBD_init() {
   KBD_buff = kmalloc(KBD_BUF_SIZE);
   kbd = kmalloc(sizeof(kbd_struct));

   kbd->read = kbd->write = 0;
   kbd->blocked = 0;
}


/*must be called from a blocking context*/

void KBD_input_loop(void *arg) {
   while(1) {
      KBD_read();
   }
}

void KBD_read() {
   CLI();
   while(kbd->read == kbd->write) {
      printk("unblocked\n");
      PROC_block_on(&kbd->blocked, 1);
      CLI();
   }
   print_char(KBD_buff[kbd->read]);
   kbd->read = (kbd->read + 1) % KBD_BUF_SIZE;

   STI();
}

void add_to_buffer(char c) {
   if ((kbd->write + 1)%KBD_BUF_SIZE != kbd->read) {
      KBD_buff[kbd->write] = c;
      kbd->write = (kbd->write + 1) % KBD_BUF_SIZE;
   }
}

char read_scancode() {
   char resp = inb(DATA);
   return convert_code(resp);
}

void kbd_isr(uint64_t irq, uint64_t err) {
   char key = read_scancode();
   if (key!= -1) {
      add_to_buffer(key);
      PROC_unblock_all(&kbd->blocked);
   }

   IRQ_end_of_interrupt((uint64_t) irq - 0x20);
}

