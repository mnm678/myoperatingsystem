#ifndef BLOCK_DEVICE
#define BLOCK_DEVICE

#include <stdint-gcc.h>
enum BlockDevType {MASS_STORAGE, PARTITION};

typedef struct BlockDev {
   uint64_t tot_length;
   int (*read_block)(struct BlockDev *dev, uint64_t blk_num, void *dst);
   uint32_t blk_size;
   enum BlockDevType type;
   const char *name;
   uint8_t fs_type;
   struct BlockDev *next;
} BlockDev;

#endif
