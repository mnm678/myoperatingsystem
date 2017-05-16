#include "interupts.h"
#include "multiboot.h"
#include "strfuncs.h"

uint64_t eightAlign(uint64_t in) {
   return (((in-1)/8) +1) * 8;
}

void* page_align(void* in) {
   /*printk("prealigned:%x\n", in);
   printk("aligned:%x\n", ((((((uint64_t)in)-1)/PAGE_SIZE)+1)*PAGE_SIZE));*/
   return (void*) ((((((uint64_t)in)-1)/PAGE_SIZE)+1)*PAGE_SIZE);
}

memory_section *memory_head = (void *)-1;

uint64_t findMemory(uint64_t ebx) {
   int k=1;
   memory_section *temp_head;
   memory_section *prev_head;
   uint64_t multibootStart = ebx;
   uint64_t current_loc = multibootStart + sizeof(uint64_t);
   multiboot_header *header = (multiboot_header*) (current_loc);
   memory_map *mem_tag;
   elf_sym *elf_tag;
   section_header *cur_section;
   uint64_t max_addr = 0;
   uint64_t min_addr = -1;
   memory_section *cur_memory_section;
   uint64_t num_memory_sections;
   int i;
   memory_element *elems;
   uint64_t tot_size = 0;


   while(header->type != 0) {
      if(header->type == MEMORY_MAP) {
         mem_tag = (memory_map*)current_loc;
         num_memory_sections = mem_tag->size/mem_tag->entsize;
         elems = (memory_element*)(mem_tag + 1);
         for (i=0; i < (num_memory_sections); i++) {
            if(elems[i].length > sizeof(memory_section) && elems[i].type == 1) {
               cur_memory_section = ((memory_section *)(elems[i].base_addr));
               /*printk("MM_addr: %x\n", cur_memory_section);*/
               cur_memory_section->size = elems[i].length;
               cur_memory_section->next = (uint64_t)memory_head;
               memory_head = cur_memory_section;
               if (tot_size < elems[i].base_addr + cur_memory_section->size) {
                  tot_size = elems[i].base_addr + cur_memory_section->size;
               }
            }
         }

      }
      else if (header->type == ELF_SYM) {
         /*while(k){};*/
         elf_tag = (elf_sym *)current_loc;
         cur_section = &elf_tag->section_headers;
         /*TODO make sure size matches*/
         for (i=0; i<elf_tag->num; i++) {
            if (cur_section->sh_type != 0) {
               if(cur_section->sh_addr < min_addr) {
                  min_addr = cur_section->sh_addr;
               }
               if (cur_section->sh_addr + cur_section->sh_size >max_addr) {
                  max_addr = cur_section->sh_addr + cur_section->sh_size;
               }

            }
            cur_section++;
         }
      }
      current_loc = current_loc + eightAlign(header->size);
      header = (multiboot_header*)current_loc;
   }

   /*printk("min:%x\n", min_addr);
   printk("max:%x\n", max_addr);*/

   /*exclude the kernel memory*/
   /*while(k){};*/
   temp_head = memory_head;
   memory_head = page_align(memory_head);
   memory_head->size = temp_head->size;
   memory_head->next = temp_head->next;

   temp_head = memory_head;
   prev_head = (void *)-1;
   while(temp_head != (void *)-1) {
      if (min_addr > (uint64_t)temp_head && max_addr < ((uint64_t)temp_head) + temp_head->size){
         /*kernel is in the middle*/
         /*make memory_section at end*/
         cur_memory_section = ((memory_section*)max_addr);
         cur_memory_section->size = temp_head->size - ((uint64_t)temp_head - max_addr);
         cur_memory_section->next = temp_head->next;
         /*update size*/
         temp_head->size = (uint64_t)temp_head - min_addr;
         temp_head->next = (uint64_t) cur_memory_section;
      }
      else if (min_addr > (uint64_t)temp_head && max_addr == ((uint64_t)temp_head + temp_head ->size)) {
         /*kernel is at the end*/
         temp_head->size = (uint64_t)temp_head - min_addr;
      }
      else if (min_addr == (uint64_t)temp_head) {
         /*kernel is at the beginning*/
         cur_memory_section = page_align(((memory_section*)max_addr));
         cur_memory_section->size = temp_head->size - (max_addr - (uint64_t)temp_head);
         cur_memory_section->next = temp_head->next;
         if (prev_head != (void*)-1) {
            prev_head->next = (uint64_t)cur_memory_section;
         }
         else {
            memory_head = cur_memory_section;
         }
         /*printk("MM_addr: %x\n", cur_memory_section);*/
         temp_head = cur_memory_section;
      }

      prev_head = temp_head;
      temp_head = page_align(temp_head);
      temp_head->size = prev_head->size;
      temp_head->next = prev_head->next;
      temp_head = (memory_section*)temp_head->next;
   }
   return page_align(tot_size);
}

free_entry *free_list_head = (void *)-1;

uint64_t next_unused_lower = 0;
uint64_t next_unused_upper = UPPER_MEM_START;

/*allocate a page frame*/
void *MMU_pf_alloc() {
   void *ret;
   memory_section *temp;
   uint64_t temp_size;
   int k=1;
   int interrupts = are_interupts_enabled();
   /*while(k){};*/

   if(interrupts) {
      CLI();
   }

   if(free_list_head != (void *)-1) {
      ret = free_list_head;
      free_list_head = (free_entry*)free_list_head->next;
      return ret;
   }

   if (memory_head == (void*)-1) {
      /*if it reaches here, we are out of space, panic*/
      /*or implement paging*/
      printk("out of memory\n");
      return (void*)-1;
   }

   /*if full, go to next*/
   if (memory_head->size < PAGE_SIZE) {
      /*printk("next memory\n");*/
      memory_head = (memory_section*)memory_head->next;
   }

   /*use what's in memory_head*/
   ret = memory_head;
   /*printk("size in current:%lx\n", memory_head->size);
   printk("addr of current:%lx\n", memory_head);*/
   temp_size = memory_head->size - PAGE_SIZE;
   /*printk("temp_size:%lx\n", temp_size);*/
   if (temp_size >=PAGE_SIZE) {
      temp = (memory_section*)memory_head->next;
      memory_head = (memory_section*)(((uint64_t) memory_head) + PAGE_SIZE);
      memory_head->size = temp_size;
      memory_head->next = (uint64_t)temp;
   }
   else {
      /*printk("next memory\n");*/
      memory_head = (memory_section*)memory_head->next;
   }

   if(interrupts) {
      STI();
   }
   return ret;

}

void *MMU_pf_calloc() {
   void *temp = MMU_pf_alloc();
   if (temp == -1) {
      /*out of memory, do something*/
      while(1) {};
   }
   memset(temp, 0, PAGE_SIZE);
   return temp;
}

/*free a page frame */
void MMU_pf_free(void* pf) {
   free_entry *next = pf;
   next->next = (uint64_t)free_list_head;
   free_list_head = next;
}
