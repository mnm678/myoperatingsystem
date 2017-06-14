#include "vfs.h"
#include "fat32.h"
#include "kmalloc.h"

FAT_SuperBlock *fsb;
uint8_t *FAT_table;

int FAT_readdir_cb(const char *name, uint64_t inode_num, void *size) {
   /*using inode_num as cluster number*/
   int k=0;
   while(k){};

   printk(name);
   printk("\n");

}

uint32_t next_cluster(uint32_t curcluster) {
   uint64_t cluster = curcluster;
   uint8_t buff[512];

   fsb->dev->read_block(fsb->dev, fsb->start_offset + fsb->num_reserved_sectors + ((cluster * 4)/512), buff);

   cluster = buff[(cluster *4)%512];

   return cluster;
}

int *FAT_read_dir(Inode *inode, readdir_cb cb, void *arg) {
   FATDirEnt entries[512/sizeof(FATDirEnt)];
   uint64_t sector_offset;
   uint32_t cluster = inode->ino_num;
   FATLongDirEnt *longent;
   int i;
   int j;
   char *name = 0;
   uint16_t order;
   FAT_Inode new_inode;
   int k=1;
   /*while(k){};*/

   while(cluster != 0 && (cluster &0xFFFFFFF) < 0xFFFFFF8) {
      printk("new cluster: %d\n", cluster);
   
      sector_offset = fsb->num_reserved_sectors + fsb->sectors_per_fat * fsb->num_fats + fsb->sectors_per_cluster *(cluster -2);
      sector_offset += fsb->start_offset;

      fsb->dev->read_block(fsb->dev, sector_offset, entries);

      for(i=0; i< (512/sizeof(FATDirEnt)); i++) {
         k=1;
         /*while(k){};*/
         if (entries[i].attr & FAT_ATTR_LFN) {
            longent = (FATLongDirEnt *) entries + i;
            if (name == 0) {
               name = kmalloc(33);
               memset(name, 0, 33);
            }
            order = (longent->order & 0x3F) - 1;
            name[13 * order] = longent->first[0];
            name[13 * order + 1] = longent->first[1];
            name[13 * order + 2] = longent->first[2];
            name[13 * order + 3] = longent->first[3];
            name[13 * order + 4] = longent->first[4];
            name[13 * order + 5] = longent->middle[0];
            name[13 * order + 6] = longent->middle[1];
            name[13 * order + 7] = longent->middle[2];
            name[13 * order + 8] = longent->middle[3];
            name[13 * order + 9] = longent->middle[4];
            name[13 * order + 10] = longent->middle[5];
            name[13 * order + 11] = longent->last[0];
            name[13 * order + 12] = longent->last[1];
         }
         else if (entries[i].attr & FAT_ATTR_HIDDEN) {
            continue;
         }
         /*else if (entries[i].size == 0){
            return;
         }*/
         else{
            if (!name) {
               name = kmalloc(13);
               memset(name, 0, 13);
               for (j=0; j<8; j++) {
                  name[j] = entries[i].name[j];
               }
               name[8] = '.';
               name[9] = entries[i].name[8];
               name[10] = entries[i].name[9];
               name[11] = entries[i].name[10];
               name[12] = 0;
            }
            
            cb(name, entries[i].cluster_lo | (entries[i].cluster_hi << 16), entries[i].size);
            name = 0;

            if (entries[i].attr & FAT_ATTR_DIRECTORY && entries[i].name[0] != '.') {
               new_inode.in.ino_num = entries[i].cluster_lo | (entries[i].cluster_hi << 16);
               new_inode.size = entries[i].size;
               FAT_read_dir(&new_inode, cb, arg);
            }


         }
      }

      cluster = next_cluster(cluster);
   }

}

SuperBlock *FAT_detect_cb(BlockDev *dev, uint64_t offset){
   FAT32 *fat;
   uint8_t buff[512];
   FAT_SuperBlock *sb;
   dev->read_block(dev, offset, buff);

   fat = (FAT32 *) buff;

   if (fat->signature ==0x28 || fat->signature == 0x29) {
      sb = kmalloc(sizeof(FAT_SuperBlock));
      sb->sb.root_inode = kmalloc(sizeof(FAT_Inode));
      sb->sb.root_inode->ino_num = fat->root_cluster_number;
      sb->sb.root_inode->read_dir = &FAT_read_dir;
      sb->sb.root_inode->cb = &FAT_readdir_cb;

      sb->sb.type = "fat32";
      sb->sectors_per_cluster = fat->bpb.sectors_per_cluster;
      sb->num_reserved_sectors = fat->bpb.reserved_sectors;
      sb->num_fats = fat->bpb.num_fats;
      if (fat->bpb.tot_sectors == 0) {
         sb->num_sectors = fat->bpb.large_sector_count;
      }
      else {
         sb->num_sectors = fat->bpb.tot_sectors;
      }
      if (fat->bpb.num_sectors_per_fat != 0) {
         sb->sectors_per_fat = fat->bpb.num_sectors_per_fat;
      }
      else {
         sb->sectors_per_fat = fat->sectors_per_fat;
      }
      sb->root_cluster_number = fat->root_cluster_number;

      sb->start_offset = offset;
      sb->dev = dev;

      return (SuperBlock *) sb;
   }
   return 0;
}

SuperBlock read_mbr(BlockDev *drive) {
   uint8_t buff[512];
   FAT_MBR *mbr;
   int k=1;
   BlockDev *bd;
   int i;
   SuperBlock *sb;

   drive->read_block(drive, 0, buff);

   mbr = (FAT_MBR *)buff;
   if (mbr->signature != 0xaa55) {
      printk("invalid boot signature\n");
      return;
   }

   printk("first sector at %lu\n", mbr->parts[0].lba_start);
   printk("%lu total sectors\n", mbr->parts[0].sec_len);
   printk("first sector at %lu\n", mbr->parts[1].lba_start);
   printk("%lu total sectors\n", mbr->parts[1].sec_len);


   for (i=0; i<4; i++) {
      sb = FAT_detect_cb(drive, mbr->parts[i].lba_start);
      if (sb != 0) {
         fsb = (FAT_SuperBlock *) sb;
      }

   }

   sb = (SuperBlock *) fsb;
   return *sb;
}
   
