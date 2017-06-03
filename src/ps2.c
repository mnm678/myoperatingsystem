#include "PS2.h"
#include "printk.h"

#define NOT_IMPLEMENTED 1
#define SHIFT 2
#define SHIFT_UP 3

int shifted = 0;

/*extern void outb(int port, char byte);
extern char inb(int port);*/

inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

void initialize_ps2() {
   uint8_t current_config;
   /*disable ports*/
   outb(CMD, 0xAD);
   outb(CMD, 0xA7);

   /*read byte 0*/
   outb(CMD, 0x20);
   /*check bit 1 of status register is clear*/
   while((inb(CMD) & OUT_STATUS) == 0){
   };
   current_config = inb(DATA);

   /*modify it*/
   current_config |= FIRST_INTERUPT;
   current_config &= ~(FIRST_CLOCK);

   current_config &= ~(SECOND_INTERUPT);
   current_config |= SECOND_CLOCK;

   /*write it back*/
   /*poll status*/
   while((inb(CMD) & IN_STATUS) != 0) {
   };
   outb(CMD, 0x60);
   while((inb(CMD) & IN_STATUS) != 0) {
   };
   outb(DATA, current_config);
}

void initialize_keyboard() {
   uint8_t resp;
   /*reset*/

   resp = 0;
   while (resp != 0xAA) {
      resp = 0;
      while((inb(CMD) & IN_STATUS) != 0) {
      };
      outb(DATA, 0xFF);
      /*read ack, then resp*/
      while((inb(CMD) & OUT_STATUS) == 0){
      };
      resp = inb(DATA);
      while((inb(CMD) & OUT_STATUS) == 0){
      };
      resp = inb(DATA);
      if (resp == 0xFC || resp == 0xFD) {
         printk("keyboard broke\n");
         return;
      }
      /*printk("%x\n", resp);*/
   }
   

   /*set scan code*/
   resp = 0;
   while (resp != 0xFA) {
      resp = 0;
      while ((inb(CMD) & IN_STATUS) != 0) {
      };
      outb(DATA, 0xF0);
      /*read the ack*/
      while((inb(CMD) & OUT_STATUS) == 0){
      };
      resp = inb(DATA);
      while ((inb(CMD) & IN_STATUS) != 0) {
      };
      outb(DATA, 1);
      /*read the ack*/
      while((inb(CMD) & OUT_STATUS) == 0){
      };
      resp = inb(DATA);
   }

   /*enable keyboard*/
   resp = 0;
   while (resp != 0xFA) {
      resp = 0;
      while((inb(CMD) & IN_STATUS) != 0) {
      };
      outb(DATA, 0xF4);
      while((inb(CMD) & OUT_STATUS) == 0){
      };
      resp = inb(DATA);
   }

}

char convert_code(uint8_t resp) {
   char cur;
   /*char scan_code_table[1000] = {0, NOT_IMPLEMENTED, 0, NOT_IMPLEMENTED,
   NOT_IMPLEMENTED, NOT_IMPLEMENTED, NOT_IMPLEMENTED, NOT_IMPLEMENTED,
   0, NOT_IMPLEMENTED, NOT_IMPLEMENTED, NOT_IMPLEMENTED,
   NOT_IMPLEMENTED, NOT_IMPLEMENTED, NOT_IMPLEMENTED, 0,
   0, NOT_IMPLEMENTED, NOT_IMPLEMENTED, 0,
   NOT_IMPLEMENTED, 'q', '1', 0,
   0, 0, 'z', 's',
   'a', 'w', '2', 0,
   0, 'c', 'x', 'd',
   'e', '4', '3', 0,
   0, ' ', 'v', 'f',
   't', 'r', '5', 0,
   0, 'n', 'b', 'h',
   'g', 'y', '6', 0,
   0, 0, 'm','j',
   'u', '7', '8', 0,
   0, ',', 'k', 'i',
   'o', '0', '9', 0,
   0, '.', '/', 'l',
   ';', 'p', '-', 0,
   0, 0, '\'', 0,
   '[', '=', 0, 0};*/
   char scan_code_table[1000] = {0, NOT_IMPLEMENTED, '1', '2',
   '3', '4', '5', '6',
   '7', '8', '9', '0',
   '-', '=', NOT_IMPLEMENTED, NOT_IMPLEMENTED,
   'q', 'w', 'e', 'r',
   't', 'y', 'u', 'i',
   'o', 'p', '[', ']',
   '\n', NOT_IMPLEMENTED, 'a', 's',
   'd', 'f', 'g', 'h',
   'j', 'k', 'l', ';',
   '\'', '`', SHIFT, '\\',
   'z', 'x', 'c', 'v',
   'b', 'n', 'm', ',',
   '.', '/', SHIFT, NOT_IMPLEMENTED,
   NOT_IMPLEMENTED, ' ', NOT_IMPLEMENTED
   };
   char shifted_scan_code_table[1000] = {0, NOT_IMPLEMENTED, '!', '@',
   '#', '$', '%', '^',
   '&', '*', '(', ')',
   '_', '+', NOT_IMPLEMENTED, NOT_IMPLEMENTED,
   'Q', 'W', 'E', 'R',
   'T', 'Y', 'U', 'I',
   'O', 'P', '{', '}',
   '\n', NOT_IMPLEMENTED, 'A', 'S',
   'D', 'F', 'G', 'H',
   'J', 'K', 'L', ':',
   '\"', '~', NOT_IMPLEMENTED, '|',
   'Z', 'X', 'C', 'V',
   'B', 'N', 'M', '<',
   '>', '?', NOT_IMPLEMENTED, NOT_IMPLEMENTED,
   NOT_IMPLEMENTED, ' ', NOT_IMPLEMENTED
   };
   /*char *printable = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
   'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
   'u', 'v', 'w', 'x', 'y', 'z', SHIFT, '`', '-', '=', 
   '[', ']', '\\', ';', '\'', ',', '.', '/', UNDEFINED];*/

   /*key released, read second byte*/
   /*if(resp == 0xF0) {
      while((inb(CMD) & OUT_STATUS) == 0) {
      };
      resp = inb(DATA);

      }
   }*/

   
   if(resp == 0xAA || resp == 0xB6) {
      shifted--;
      return -1;
   }
   else if (resp < 0x3A) {
      if (scan_code_table[resp] == SHIFT) {
         shifted++;
         return -1;
      }
      else if (shifted > 0) {
         return shifted_scan_code_table[resp];
      }
      else {
         return scan_code_table[resp];
      }
   }
   else {
      return -1;
   }
}

void print_char(char cur) {
   if (cur == -1) {
      return;
   }
   /*else if(resp < 0x3A){*/
      if (cur == 0) {
         printk("invalid scan code\n");
      }
      else if(cur == NOT_IMPLEMENTED) {
         printk("not implemented\n");
      }
      else {
         printk("%c", cur);
      }
   /*}*/

   /*printk("%x\n", resp);*/
}

void read_and_print() {
   int k = 1;
   uint8_t resp;
   char key;
   while((inb(CMD) & OUT_STATUS) == 0) {
   };
   resp = inb(DATA);

   /*while(k){};*/

   key = convert_code(resp);
   if (key != -1){
      print_char(key);
   }
}
