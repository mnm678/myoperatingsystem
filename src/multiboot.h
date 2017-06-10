#ifndef MULTIBOOT
#define MULTIBOOT

#define BASIC_MEM 4
#define MEMORY_MAP 6
#define ELF_SYM 9
#include <stdint-gcc.h>
#include "printk.h"
#include "types.h"

/*in kilobytes*/
/*uint64_t lowerMem = 0;
uint64_t upperMem = 0;*/

typedef struct memory_section{
   uint64_t next;
   uint64_t size;
}__attribute__((packed)) memory_section;

typedef struct multiboot_header{
   uint32_t type;
   uint32_t size;
}__attribute__((packed)) multiboot_header;

typedef struct basic_memory {
   uint32_t type;
   uint32_t size;
   uint32_t mem_lower;
   uint32_t mem_upper;
}__attribute__((packed)) basic_memory;

typedef struct section_header {
   uint32_t sh_name;
   uint32_t sh_type;
   uint64_t sh_flags;
   uint64_t sh_addr;
   uint64_t sh_offset;
   uint64_t sh_size;
   uint32_t sh_link;
   uint32_t sh_info;
   uint64_t sh_addralign;
   uint64_t sh_entsize;
}__attribute__((packed)) section_header;

typedef struct elf_sym {
   uint32_t type;
   uint32_t size;
   uint32_t num;
   uint32_t entsize;
   uint32_t string_table;
   section_header section_headers;
}__attribute__((packed)) elf_sym;

typedef struct memory_map {
   uint32_t type;
   uint32_t size;
   uint32_t entsize;
   uint32_t entver;
}__attribute__((packed)) memory_map;

typedef struct memory_element {
   uint64_t base_addr;
   uint64_t length;
   uint32_t type;
   uint32_t res;
}__attribute__((packed)) memory_element;

uint64_t eightAlign(uint64_t in);

uint64_t findMemory(uint64_t ebx);

typedef struct free_entry {
   uint64_t next;
} free_entry;

#define UPPER_MEM_START (1024 * 1024)

#define PAGE_SIZE 4096

/*allocate a page frame*/
void *MMU_pf_alloc();
void *MMU_pf_calloc();

/*free a page frame */
void MMU_pf_free(void* pf);

#endif
