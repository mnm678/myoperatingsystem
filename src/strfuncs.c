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

int strcmp(const char *s1, const char *s2) {
   int i;
   int res;
   if ((res = strlen(s1) - strlen(s2))) {
      return res;
   }  
   for (i=0; i<strlen(s1); i++) {
      if ((res = s1[i] - s2[i])) {
         return res;
      }
   }
   return 0;
}
/*void *memcpy(void *dest, void *src, size_t n) {
*/

void *memset(void *s, int c, size_t n) {
   char *mem = s;
   while(n) {
      mem[--n] = c;
   }
   return s;
}

void *memmove(void *dest, const void *src, size_t n) {
   char temp[n];
   int i;
   for (i=0; i < n; i++) {
      temp[i] = ((char*)src)[i];
   }
   for (i=0; i < n; i++) {
      ((char*)dest)[i] = temp[i];
   }
   return dest;
}
