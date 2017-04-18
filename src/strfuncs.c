#include <stddef.h>
#include <stdarg.h>

extern size_t strlen(const char *s) {
   char *temp = s;
   size_t count = 0;

   while(*s != 0) {
      count++;
      s++;
   }

   return count;
}
