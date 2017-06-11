#ifndef VFS
#define VFS

#include "block_device.h"
#include "printk.h"

typedef struct SuperBlock *(*FS_detect_cb)(BlockDev *dev);
extern void FS_register(FS_detect_cb probe);

typedef struct MBR_Partition {
   uint8_t status;
   uint8_t first_sector_head;
   uint8_t first_sector_high;
   uint8_t first_sector_low;
   uint8_t part_type;
   uint8_t last_sector_head;
   uint8_t last_sector_high;
   uint8_t last_sector_low;
   uint32_t first_sector_lba;
   uint32_t sectors_in_part;
}__attribute__ ((packed)) MBR_Partition;

typedef struct MBR {
   uint8_t bootstrap[446];
   MBR_Partition parts[4];
   uint16_t signature;
}__attribute__ ((packed)) MBR;

#endif
