#define SERIAL_PORT 0x3f8
#define SERIAL_BUF_LEN 4096

#include "serial.h"
#include "interupts.h"

char serial_buf[SERIAL_BUF_LEN];
uint16_t head;
uint16_t tail;
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

void serial_write_char(char c) {
   int interupts = are_interupts_enabled();
   int first = 0;

   if(interupts) {
      CLI();
   }
   if(head == tail) {
      first = 1;
   }
   /*if there isn't space, the data will be lost*/
   if ((tail + 1)%SERIAL_BUF_LEN != head) {
      /*there's space*/
      serial_buf[tail] = c;
      tail++;
   }
   if(interupts) {
      STI();
   }

   if(first) {
      asm("int $0x24");
   }
}

void serial_write(char *buff, int len) {
   int i;
   for (i = 0; i<len; i++) {
      serial_write_char(buff[i]);
   }
}

void serial_interupt(void *irq) {
   /*check iir*/
   char iir = inb(SERIAL_PORT + 2);

   if (6 & iir) {
      /*line status change*/
      inb(SERIAL_PORT + 3);
      return;
   }
   
   if (!(4 & iir)) {
      outb(SERIAL_PORT, serial_buf[head]);
      head++;
   }
   else {
      /*hw buffer is full*/
      return;
   }

}
