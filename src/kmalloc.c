#include "kmalloc.h"

typedef struct memChunks {
   uint32_t size;
   uint8_t free;
   struct memChunks *next;
} memChunks;

memChunks *malloc_head = 0;

int checkErr(int err) {
   if (err == -1) {
      printk("MALLOC error");
      return 1;
   }
   return 0;
}

int makeDivisible(int size) {
   return ((size - 1)/16 + 1) * 16;
}

void useExtraSpace(memChunks *chunk, int useableSize) {
   int headSize = makeDivisible(sizeof(memChunks));
   memChunks *temp;
   if (chunk->size > useableSize + headSize) {
      temp = chunk->next;
      chunk->next = (memChunks *)((uintptr_t)chunk + useableSize + headSize);
      chunk->next->free = 1;
      chunk->next->size = chunk->size - useableSize - headSize;
      chunk->size = useableSize;
      chunk->next->next = temp;
   }
}

void *kmalloc(size_t size) {
   int useableSize = makeDivisible(size);
   memChunks *chunk = 0;
   void *retVal;
   int realBreakSize;
   void *sbrkBottom;
   int headSize = makeDivisible(sizeof(memChunks));
   int err;

   if (size <= 0) {
      return NULL;
   }
   if (malloc_head) {
      /*look for space*/
      chunk = malloc_head;
      while(chunk) {
         if(chunk->free && chunk->size >= useableSize) {
            /*found space*/
            retVal = (memChunks *)(((uintptr_t)chunk) + headSize);

            chunk->free = 0;
            useExtraSpace(chunk, useableSize);

            return retVal;
         }
         chunk = chunk->next;
      }
      /* didn't find space, need to create more space */
   }
   else {
      /*first call of malloc*/
      malloc_head = (memChunks *)(sbrk(0));
      if (checkErr((uintptr_t)malloc_head)) {
         return NULL;
      }
      if ((uintptr_t)malloc_head % 16) {
         /*initial address not divisible by 16 */
         malloc_head = (memChunks *) sbrk((16 - ((uintptr_t)malloc_head % 16)/PAGE_SIZE));
         if (checkErr((uintptr_t)malloc_head)) {
            return NULL;
         }
      }
      chunk = malloc_head;
   }
   /*if it reaches here, need to call sbrk*/
   sbrkBottom = sbrk(0);
   if (checkErr((uintptr_t)sbrkBottom)) {
      return NULL;
   }
   if (useableSize <= BREAK_SIZE - headSize) {
      realBreakSize = BREAK_SIZE;
   }
   else{
      realBreakSize = (useableSize/BREAK_SIZE + 1) * BREAK_SIZE;
   }
   err = (uintptr_t)sbrk(realBreakSize/PAGE_SIZE);
   if (checkErr(err)) {
      return NULL;
   }

   /*chunk set to head if first call*/
   if (!chunk) {
      chunk = malloc_head;
      while(chunk->next) {
         chunk = chunk->next;
      }
      chunk->next = (memChunks *)sbrkBottom;
      chunk = chunk->next;
   }
   chunk->next = 0;

   if(realBreakSize - useableSize - headSize > headSize) {
      /*there is room for more chunks*/
      chunk->next = (memChunks *) ((uintptr_t)chunk + useableSize + headSize);
      chunk->next->free = 1;
      chunk->next->size = realBreakSize - 2 * headSize - useableSize;
      chunk->next->next = 0;
   }
   
   chunk->size = useableSize;
   chunk->free = 0;
   retVal = (memChunks *)((uintptr_t)chunk + headSize);
   return retVal;
}

void *kcalloc(size_t nmemb, size_t size){
   memChunks *temp;

   int useableSize = makeDivisible(size);
   temp = kmalloc(nmemb * size);
   /*errno already set in malloc if error*/
   memset(temp, 0, size * nmemb);
   return temp;
}

void kfree(void *ptr) {
   memChunks *chunk = 0;
   memChunks *prev = 0;
   int headSize = makeDivisible(sizeof(memChunks));

   if (!ptr) {
      return;
   }

   chunk = malloc_head;
   while(chunk) {
      if((uintptr_t)chunk + headSize <= (uintptr_t)ptr && 
         (uintptr_t)chunk + headSize + chunk->size > (uintptr_t)ptr) {
         /*found the chunk!*/
         chunk->free = 1;
         if (prev && prev->free) {
            /*combine with previous block */
            prev->size += chunk->size + headSize;
            prev->next = chunk->next;
            chunk = prev;
         }
         if (chunk->next && chunk->next->free) {
            /*combine with next block*/
            chunk->size += chunk->next->size + headSize;
            chunk->next = chunk->next->next;
         }
         return;
      }
      prev = chunk;
      chunk = chunk->next;
   }
}

void *realloc(void *ptr, size_t size) {
   memChunks *chunk = 0;
   int headSize = makeDivisible(sizeof(memChunks));
   int useableSize = makeDivisible(size);
   void *retVal;
   int realBreakSize;
   int err;
   int tempSize;

   if (ptr == NULL) {
      retVal = kmalloc(size);
      return retVal;
   }
   if (size == 0) {
      kfree(ptr);
      return NULL;
   }
   
   chunk = malloc_head;
   while (chunk) {
      if ((uintptr_t)chunk + headSize <= (uintptr_t)ptr && 
         (uintptr_t)chunk + headSize + chunk->size > (uintptr_t)ptr) {
         /* found the chunk! */
         if (size <= chunk->size) {
            /*there is extra space*/
            retVal = (memChunks *)((uintptr_t)chunk + headSize);
            if (chunk->size - useableSize - headSize > 0) {
               /*it's useable space*/
               useExtraSpace(chunk, useableSize);
               /*combine memory and set to free*/
               kfree(chunk->next);
            }

            return retVal;
         }

         if (chunk->next && chunk->next->free) {
            /*space in the next chunk*/
            chunk->size += chunk->next->size + headSize;
            chunk->next = chunk->next->next;
         }
         if (size > chunk->size && !chunk->next) {
            /*this is the last chunk, can sbrk and have more space*/
            if (size - chunk->size - BREAK_SIZE >= 0) {
               realBreakSize = BREAK_SIZE;
            }
            else{
               realBreakSize = 
                  (((size - chunk->size) - 1)/BREAK_SIZE + 1) * BREAK_SIZE;
            }
            err = (uintptr_t)sbrk(realBreakSize/PAGE_SIZE);
            if (checkErr(err)) {
               return NULL;
            }

            chunk->size += realBreakSize;

         }

         /*have a block with all available memory*/
         if (size <= chunk->size) {
            retVal = (memChunks *)((uintptr_t)chunk + headSize);
            /*there is extra space*/
            useExtraSpace(chunk, useableSize);

            return retVal;
         }
         else {
            /*need more space*/

            /*size could change in free*/
            tempSize = chunk->size;
            retVal = kmalloc(useableSize);
            memmove(retVal, (memChunks *)((uintptr_t)chunk + headSize),
                  tempSize);
            kfree(chunk);
            return retVal;

         }
      }
      chunk = chunk->next;
   }

   /*allocated memory not found*/
   return NULL;
}
