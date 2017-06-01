#ifndef VIRTUAL_ALLOCATORH
#define VIRTUAL_ALLOCATORH

#include "multiboot.h"

typedef struct CR3_entry {
   uint64_t res:12;
   uint64_t base_addr:40;
   uint64_t res2:12;
} CR3_entry;

typedef struct pt_entry {
   uint64_t p:1;
   uint64_t rw:1;
   uint64_t flags:3;
   uint64_t a:1;
   uint64_t res:3;
   uint64_t avl:3;
   uint64_t base_addr:40;
   uint64_t avl2:11;
   uint64_t nx:1;
} pt_entry;

typedef struct virtual_addr {
   uint64_t pf_ndx:12;
   uint64_t l1_ndx:9;
   uint64_t l2_ndx:9;
   uint64_t l3_ndx:9;
   uint64_t l4_ndx:9;
   uint64_t pad:16;
}__attribute__((packed)) virtual_addr;

union virt{
   uint64_t i;
   virtual_addr va;
};

uint64_t getCR3();

pt_entry *setup_pt(virtual_addr, uint64_t);
void connect_addr(virtual_addr virt, uint64_t phy, uint64_t l4);

void *add_kstack();
void *MMU_alloc_page();
void *MMU_alloc_pages(int num);
void MMU_free_page();
void MMU_free_pages(int num);


void setup_id_map(uint64_t phy_mem_size);

#endif
