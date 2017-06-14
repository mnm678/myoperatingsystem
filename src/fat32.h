#ifndef FAT32_H
#define FAT32_H

#include "vfs.h"

#define FAT_ATTR_READ_ONLY 0x01
#define FAT_ATTR_HIDDEN 0x02
#define FAT_ATTR_SYSTEM 0x04
#define FAT_ATTR_VOLUME_ID 0x08
#define FAT_ATTR_DIRECTORY 0x10
#define FAT_ATTR_ARCHIVE 0x20
#define FAT_ATTR_LFN (FAT_ATTR_READ_ONLY | FAT_ATTR_HIDDEN | \
FAT_ATTR_SYSTEM | FAT_ATTR_VOLUME_ID)

typedef struct FAT_MBR_Partition {
   uint8_t status;
   uint8_t first_sector_head;
   uint8_t first_sector_high;
   uint8_t first_sector_low;
   uint8_t part_type;
   uint8_t last_sector_head;
   uint8_t last_sector_high;
   uint8_t last_sector_low;
   uint32_t lba_start;
   uint32_t sec_len;
}__attribute__ ((packed)) FAT_MBR_Partition;

typedef struct MBR {
   uint8_t bootstrap[446];
   FAT_MBR_Partition parts[4];
   uint16_t signature;
}__attribute__ ((packed)) FAT_MBR;

typedef struct FAT_BPB {
   uint8_t jmp[3];
   char oem_id[8];
   uint16_t bytes_per_sector;
   uint8_t sectors_per_cluster;
   uint16_t reserved_sectors;
   uint8_t num_fats;
   uint16_t num_dirents;
   uint16_t tot_sectors;
   uint8_t mdt;
   uint16_t num_sectors_per_fat;
   uint16_t sectors_per_track;
   uint16_t num_heads;
   uint32_t num_hidden_sectors;
   uint32_t large_sector_count;
}__attribute__((packed)) FAT_BPB;

typedef struct FAT32 {
   FAT_BPB bpb;
   uint32_t sectors_per_fat;
   uint16_t flags;
   uint8_t maj_vers;
   uint8_t min_vers;
   uint32_t root_cluster_number;
   uint16_t fsinfo_sector;
   uint16_t backup_boot_sector;
   uint8_t zero[12];
   uint8_t drive_num;
   uint8_t ntflags;
   uint8_t signature;
   uint32_t serial_num;
   char label[11];
   char sys_id[8];
   uint8_t boot_code[420];
   uint8_t boot_sig[2];
}__attribute__((packed)) FAT32;

typedef struct FAT_SuperBlock{
   SuperBlock sb;
   uint8_t sectors_per_cluster;
   uint16_t num_reserved_sectors;
   uint8_t num_fats;
   uint32_t num_sectors;
   uint32_t sectors_per_fat;
   uint32_t root_cluster_number;
   uint64_t start_offset;
   BlockDev *dev;
} FAT_SuperBlock;

typedef struct FAT_Inode {
   Inode in;
   uint64_t size;
} FAT_Inode;

typedef struct FATDirEnt {
   char name[11];
   uint8_t attr;
   uint8_t nt;
   uint8_t ct_tenths;
   uint16_t ct;
   uint16_t cd;
   uint16_t ad;
   uint16_t cluster_hi;
   uint16_t mt;
   uint16_t md;
   uint16_t cluster_lo;
   uint32_t size;
}__attribute__((packed)) FATDirEnt;

typedef struct FATLongDirEnt {
   uint8_t order;
   uint16_t first[5];
   uint8_t attr;
   uint8_t type;
   uint8_t checksum;
   uint16_t middle[6];
   uint16_t zero;
   uint16_t last[2];
}__attribute__((packed)) FATLongDirEnt;

SuperBlock read_mbr(BlockDev *);




#endif
