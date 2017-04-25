#include <stddef.h>
#include <stdarg.h>

extern size_t strlen(char *s) {
   char *temp = s;
   size_t count = 0;

   while(*temp != 0) {
      count++;
      temp++;
   }

   return count;
}
