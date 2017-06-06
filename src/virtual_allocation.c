#include "virtual_allocation.h"

/*2MB*/
#define STACK_SIZE 2097152
#define MAX_STACK 1024

void setCR3(uint64_t CR3) {
   asm("mov %0, %%cr3;" :: "r" ( CR3 ));
}

uint64_t getCR3() {
   uint64_t CR3;
   asm("mov %%cr3, %0;" : "=r" (CR3));
   return CR3;
}

uint64_t stack_start;
uint16_t stack_count = 0;

pt_entry *setup_pt(virtual_addr virt, uint64_t base) {
   pt_entry *l4 = (pt_entry*)base;
   pt_entry *l3, *l2, *l1;

   /*l3*/
   if (!l4[virt.l4_ndx].p) {
      l4[virt.l4_ndx].base_addr = (uint64_t) MMU_pf_calloc() >> 12;
      l4[virt.l4_ndx].p = 1;
      l4[virt.l4_ndx].rw=1;
   }
   l3 = l4[virt.l4_ndx].base_addr << 12;

   /*l2*/
   if (!l3[virt.l3_ndx].p) {
      l3[virt.l3_ndx].base_addr = (uint64_t)MMU_pf_calloc() >>12;
      l3[virt.l3_ndx].p = 1;
      l3[virt.l3_ndx].rw = 1;
   }
   l2 = l3[virt.l3_ndx].base_addr << 12;

   /*l1*/
   if (!l2[virt.l2_ndx].p) {
      l2[virt.l2_ndx].base_addr = (uint64_t)MMU_pf_calloc() >> 12;
      l2[virt.l2_ndx].p = 1;
      l2[virt.l2_ndx].rw = 1;
   }
   l1 = l2[virt.l2_ndx].base_addr <<12;

   return l1;
}

void connect_addr(virtual_addr virt, uint64_t phy, uint64_t base) {
   pt_entry *l1;

   l1 = setup_pt(virt, base);

   /*l0*/
   if (!l1[virt.l1_ndx].p) {
      l1[virt.l1_ndx].base_addr = phy >> 12;
      l1[virt.l1_ndx].p = 1;
      l1[virt.l1_ndx].rw = 1;
   }
}

void initialize_stack(void *stack) {
   int i;
   union virt j;
   pt_entry *l1;
   int size = STACK_SIZE/PAGE_SIZE;

   int k = 1;
   /*while(k) {};*/

   for(i=0; i < size; i++) {
      j.i = (uint64_t) stack + (i*PAGE_SIZE);
      l1 = setup_pt(j.va, getCR3());
      /*mark as used*/
      l1[j.va.l1_ndx].avl =1;
   }
}


void *add_kstack() {
   void *stack;

   if (stack_count >= MAX_STACK) {
      printk("out of kstack space\n");
      return -1;
   }

   stack = stack_start + STACK_SIZE *stack_count;
   stack_count++;
   initialize_stack(stack);

   /*stacks grow up*/
   return stack + STACK_SIZE - PAGE_SIZE;
}

void free_stack(void* stack) {
   /*TODO*/
}

uint64_t heap_bottom = 0;

void *MMU_alloc_page() {
   uint64_t CR3 = getCR3();
   void *phy = MMU_pf_alloc();
   union virt j;
   pt_entry *l1;

   int k = 1;
   /*while(k){};*/

   
   if (heap_bottom == 0) {
      heap_bottom = stack_start + STACK_SIZE*MAX_STACK;
   }

   j.i = heap_bottom;
   l1 = setup_pt(j.va, CR3);

   l1[j.va.l1_ndx].avl = 1;

   heap_bottom += PAGE_SIZE;

   return heap_bottom - PAGE_SIZE;
}

void *MMU_alloc_pages(int num) {
   void *temp = -1;
   int i;

   for (i = 0; i < num; i++) {
      if (temp == -1){
         temp = MMU_alloc_page();
      }
      else {
         MMU_alloc_page();
      }
   }
   if (temp == -1) {
      if (heap_bottom == 0) {
         heap_bottom = stack_start + STACK_SIZE*MAX_STACK;
      }
      temp = heap_bottom;
   }
   return temp;
}

/*moves the heap_bottom up*/
void MMU_free_page() {
   union virt virt_pg;
   virt_pg.i = heap_bottom - PAGE_SIZE;
   virtual_addr virt = virt_pg.va;
   pt_entry *l1 = setup_pt(virt, getCR3());
   MMU_pf_free(l1[virt.l1_ndx].base_addr << 12);
   l1[virt.l1_ndx].p = 0;
   l1[virt.l1_ndx].avl = 0;

   heap_bottom -= PAGE_SIZE;
}

void MMU_free_pages(int num) {
   int i;

   for (i=0; i<num;i++) {
      MMU_free_page();
   }
}

void setup_id_map(uint64_t phy_mem_size) {
   pt_entry *l4 = MMU_pf_calloc();
   uint64_t i;
   union virt j;
   int k=1;

   stack_start = phy_mem_size;

   printk("stack start: %x\n", stack_start);

   for(i=0; i < phy_mem_size/PAGE_SIZE; i++){
      j.i = i * PAGE_SIZE;
      connect_addr(j.va, j.i, l4);
   }

   setCR3((uint64_t)l4);

}

