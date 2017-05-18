#pragma once

#define sbrk MMU_alloc_pages
#define BUF_SIZE 70
#define BREAK_SIZE 65536

#include "types.h"
#include "strfuncs.h"
#include "virtual_allocation.h"
#include <stdint-gcc.h>

void *kmalloc(size_t size);
void *kcalloc(size_t nmemb, size_t size);
void kfree(void *ptr);
