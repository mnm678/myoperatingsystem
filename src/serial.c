#define SERIAL_PORT 0x3f8
#define SERIAL_BUF_LEN 4096

#include "serial.h"
#include "interrupts.h"

char serial_buf[SERIAL_BUF_LEN];
uint32_t head;
uint32_t tail;
int busy;

void serial_setup() {
   outb(SERIAL_PORT + 1, 0x00);
   outb(SERIAL_PORT + 3, 0x80);
   outb(SERIAL_PORT + 0, 0x03);
   outb(SERIAL_PORT + 1, 0x00);
   outb(SERIAL_PORT + 3, 0x03);
   outb(SERIAL_PORT + 2, 0xC7);
   outb(SERIAL_PORT + 4, 0x0B);
   head = tail = 0;
}

int is_transmit_empty() {
   return inb(SERIAL_PORT + 5) & 0x20;
}

int BB_busy = 0;

void serial_write_char(char c) {
   int interrupts = are_interrupts_enabled();
   int k=1;

   if(interrupts) {
      CLI();
   }

   BB_busy = !(is_transmit_empty());

   /*if there isn't space, the data will be lost*/
   if ((tail + 1)%SERIAL_BUF_LEN != head) {
      /*there's space*/
      serial_buf[tail] = c;
      tail = (tail + 1) % SERIAL_BUF_LEN;
   }

   if(!BB_busy) {
      /*while(k) {};*/
      serial_interrupt(0);
   }

   if(interrupts) {
      STI();
   }
}

void serial_write(char *buff, int len) {
   int i;
   for (i = 0; i<len; i++) {
      serial_write_char(buff[i]);
   }
}

void serial_interrupt(void *irq) {
   /*check iir*/
   char iir = inb(SERIAL_PORT + 2);

   if (6 & iir) {
      /*line status change*/
      inb(SERIAL_PORT + 3);
      return;
   }
   
   if (!(4 & iir)) {
      if(head != tail) {
         outb(SERIAL_PORT, serial_buf[head]);
         head = (head + 1)%SERIAL_BUF_LEN;
         BB_busy = 1;
      }
      else {
         BB_busy = 0;
      }
   }
   else {
      /*hw buffer is full*/
      BB_busy = 1;
      return;
   }

}
