#include "VGA_Driver.h"
#include <stdarg.h>
#include <limits.h>
#include "interrupts.h"
#include "serial.h"
#include "strfuncs.h"

void display_char(char c) {
   VGA_display_char(c);
   serial_write_char(c);
}

void display_str(char *s) {
   VGA_display_str(s);
   serial_write(s, strlen(s));
}

void print_uint(unsigned long long in) {
   unsigned long long temp = in;
   unsigned long long var = in;
   long long pow;
   int i = 0;
   int digit;

   /*number of digits*/
   while((var = var/10) > 0) {
      i++;
   }

   pow = 1;
   while (i--) {
      pow = pow * 10;
   }

   while (pow >= 1) {
      digit = temp/pow;
      display_char('0' + digit);
      temp -= digit * pow;

      pow = pow / 10;
      if (pow == 1  && i == 1) {
         pow = 0;
      }
      else if (pow == 1) {
         i = 1;
      }
   }
}

void print_hex(unsigned long long in) {
   unsigned long long temp = in;
   unsigned long long var = in;
   long long pow;
   int i = 0;
   int digit;

   /*number of digits*/
   while((var = var/16) > 0) {
      i++;
   }

   pow = 1;
   while (i--) {
      pow = pow * 16;
   }

   while (pow >= 1) {
      digit = temp/pow;
      if (digit < 10) {
         display_char('0' + digit);
      }
      else {
         display_char('a' + digit - 10);
      }
      temp -= digit * pow;

      if (pow == 1) {
         i = 1;
      }

      pow = pow / 16;
      if (pow == 1  && i == 1) {
         pow = 0;
      }
   }
}


void print_int(long long in) {
   unsigned long long temp;
   unsigned long long var;
   long long pow;
   int i = 0;
   int digit;
   if (in < 0) {
      display_char('-');
      temp = in - 1;
      temp = ~temp;
   }
   else {
      temp = in;
   }
   var = temp;

   /*number of digits*/
   while((var = var/10) > 0) {
      i++;
   }

   pow = 1;
   while (i--) {
      pow = pow * 10;
   }

   while (pow >= 1) {
      digit = temp/pow;
      display_char('0' + digit);
      temp -= digit * pow;

      pow = pow / 10;
      if (pow == 1  && i == 1) {
         pow = 0;
      }
      else if (pow == 1) {
         i = 1;
      }
   }
}

extern int printk(const char *fmt, ...) {
   va_list va;
   va_start(va, fmt);
   int count = 0;
   int interrupts = are_interrupts_enabled();

   if(interrupts) {
      CLI();
   }
   
   while (*fmt != 0) {
      if (*fmt == '%') {
         switch(*(fmt+1)) {
            case '%':
               display_char('%');
               break;
            case 'd':
               print_int((long long)va_arg(va, int));
               break;
            case 'u':
               print_uint(va_arg(va, unsigned int));
               break;
            case 'x':
               print_hex(va_arg(va, int));
               break;
            case 'c':
               display_char(va_arg(va, int));
               break;
            case 'p':
               print_hex((long)va_arg(va, void*));
               break;
            case 'h':
               switch(*(fmt+2)) {
                  case 'd':
                     print_int(va_arg(va, int));
                     break;
                  case 'u':
                     print_uint(va_arg(va, unsigned int));
                     break;
                  case 'x':
                     print_hex(va_arg(va, int));
                     break;
               }
               fmt++;
               break;
            case 'l':
               switch(*(fmt+2)) {
                  case 'd':
                     print_int(va_arg(va, long));
                     break;
                  case 'u':
                     print_uint(va_arg(va, unsigned long));
                     break;
                  case 'x':
                     print_hex(va_arg(va, long));
                     break;
               }
               fmt++;
               break;
            case 'q':
               switch(*(fmt+2)) {
                  case 'd':
                     print_int(va_arg(va, long long));
                     break;
                  case 'u':
                     print_uint(va_arg(va, unsigned long long));
                     break;
                  case 'x':
                     print_hex(va_arg(va, long long));
                     break;
               }
               fmt++;
               break;
            case 's':
               display_str(va_arg(va, char*));
               break;
         }

         fmt++;

      }
      else {
         display_char(*fmt);
      }

      count++;

      fmt++;
   }

   va_end(va);

   if(interrupts) {
      STI();
   }
   return count;
}
