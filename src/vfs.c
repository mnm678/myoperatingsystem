#include "vfs.h"

void read_mbr(BlockDev *drive) {
   uint8_t buff[512];
   MBR *mbr;

   drive->read_block(drive, 0, buff);

   mbr = (MBR *)buff;
   if (mbr->signature != 0xaa55) {
      printk("invalid boot signature\n");
      return;
   }

   printk("first sector at %lu\n", mbr->parts[0].first_sector_lba);
   printk("%lu total sectors\n", mbr->parts[0].sectors_in_part);
   printk("first sector at %lu\n", mbr->parts[1].first_sector_lba);
   printk("%lu total sectors\n", mbr->parts[1].sectors_in_part);
}
   
