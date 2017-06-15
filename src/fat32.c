#include "vfs.h"
#include "fat32.h"
#include "kmalloc.h"

FAT_SuperBlock *fsb;
uint8_t *FAT_table;

uint32_t next_cluster(uint32_t curcluster) {
   uint64_t cluster = curcluster;
   uint8_t buff[512];
   int k=0;
   while(k){};

   fsb->dev->read_block(fsb->dev, fsb->start_offset + fsb->num_reserved_sectors + ((cluster *4)/512), buff);

   cluster = *((uint32_t *)&buff[(cluster *4)%512]) & 0xFFFFFFF;

   return cluster;
}

int FAT_read(File *file, char *dst, size_t len) {
   uint64_t cluster = file->inode->ino_num;
   int64_t size = len;
   uint32_t offset;
   printk("len: %d\n", len);

   while(size > 0) {
      offset = file->offset;
      fsb->dev->read_block(fsb->dev, offset, dst + (len - size));
      cluster = next_cluster(cluster);

      if (size < 512) {
         file->offset += size;
      }
      else {
         file->offset = fsb->num_reserved_sectors + fsb->sectors_per_fat * fsb->num_fats + fsb->sectors_per_cluster *(cluster-2);
         file->offset += fsb->start_offset;
         printk("sectors peroffset: %d\n", fsb->sectors_per_cluster);
      }
      size -= 512;
   }
}

int FAT_lseek(File *file, size_t off) {
   file->offset += off;
}

int FAT_close(File **f) {
   kfree(*f);
   return 0;
}

File *FAT_open(struct Inode *inode) {
   File *ret = kmalloc(sizeof(File));
   int sector_offset;
   sector_offset = fsb->num_reserved_sectors + fsb->sectors_per_fat * fsb->num_fats + fsb->sectors_per_cluster *(inode->ino_num -2);
   sector_offset += fsb->start_offset;

   ret->inode = inode;
   ret->offset = sector_offset;
   ret->read = FAT_read;
   /*ret->write = FAT_write;*/
   ret->lseek = FAT_lseek;
   ret->close = FAT_close;
   
}

int read_test() {
   char *buff = kmalloc(3000);
   memset(buff, 0, 3000);
   File *f;
   Inode *node;
   Path *head = kmalloc(sizeof(Path));
   Path *next = kmalloc(sizeof(Path));
   int k = 1;
   while(k){};

   head->next = next;
   head->cur = "test";
   next->cur = "testfile";
   next->next = 0;
   node = find_file(head);

   f= node->open(node);
   f->read(f, buff, node->size);

   printk(buff);

}

FAT_Inode *find_file(Path *head) {
   Path *path = head;
   readdir_arg args;
   Inode *cur = fsb->sb.root_inode;
   while (path) {
      args.name = path->cur;
      FAT_read_dir(cur, FAT_readdir_cb, &args);
      cur = args.inode;
      path  = path->next;
   }

   return cur;

}

int FAT_listall_cb(const char *name, uint64_t inode_num, void *dir_arg) {

   readdir_arg *arg = (readdir_arg *) dir_arg;

   printk(name);
   printk("\n");

   if (arg->directory && name[0] != '.') {
      FAT_read_dir(arg->inode, FAT_listall_cb, dir_arg);
   }

   return 0;
}

FAT_list_all() {
   int k = 0;
   readdir_arg arg;
   while(k){};
   FAT_read_dir(fsb->sb.root_inode, FAT_listall_cb, &arg);
}     

/*return 0 to keep traversing, 1 to stop*/
int FAT_readdir_cb(const char *name, uint64_t inode_num, void *dir_arg) {
   /*using inode_num as cluster number*/
   readdir_arg *arg = (readdir_arg *) dir_arg;
   Inode *in = arg->inode;
   int k=0;
   while(k){};
   char *to_cmp = arg->name;

   printk(name);
   printk("\n");

   if (!strcmp(name, to_cmp)) {
      return 1;
      /*FAT_read_dir(in, FAT_readdir_cb, arg);*/
   }
   return 0;

}

int FAT_read_dir(Inode *inode, readdir_cb cb, void *arg) {
   FATDirEnt entries[512/sizeof(FATDirEnt)];
   uint64_t sector_offset;
   uint32_t cluster = inode->ino_num;
   FATLongDirEnt *longent;
   int i;
   int j;
   char *name = 0;
   uint16_t order;
   FAT_Inode *new_inode;
   int k=0;
   readdir_arg *read_arg = (readdir_arg *)arg;
   /*while(k){};*/

   while(cluster != 0 && (cluster &0xFFFFFFF) < 0xFFFFFF8) {
      k=0;
      while(k){};
   
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
         else if (entries[i].name[0] == 0xE5) {
            continue;
         }
         /*else if (entries[i].size == 0){
            return;
         }*/
         else if (entries[i].name[0] == 0 || entries[i].name[0] == 127) {
            return;
         }
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
            
            new_inode = kmalloc(sizeof(FAT_Inode));
            memset(new_inode, 0, sizeof(FAT_Inode));

            new_inode->in.ino_num = entries[i].cluster_lo | (entries[i].cluster_hi << 16);
            new_inode->in.size = entries[i].size;
            new_inode->in.open = FAT_open;
            read_arg->inode = new_inode;
            read_arg->directory = entries[i].attr & FAT_ATTR_DIRECTORY;
            if (cb(name, entries[i].cluster_lo | (entries[i].cluster_hi << 16), read_arg)) {
               return;
            }
            name = 0;

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
      sb->sb.root_inode->open = FAT_open;
      /*TODO: determine size*/
      sb->sb.root_inode->size = 512;

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

   printk("boot signature:%x\n", mbr->signature);
   printk("first sector at %lu\n", mbr->parts[0].lba_start);
   printk("%lu total sectors\n", mbr->parts[0].sec_len);
   printk("first sector at %lu\n", mbr->parts[1].lba_start);
   printk("%lu total sectors\n", mbr->parts[1].sec_len);
   printk("first sector at %lu\n", mbr->parts[2].lba_start);
   printk("%lu total sectors\n", mbr->parts[2].sec_len);
   printk("first sector at %lu\n", mbr->parts[3].lba_start);
   printk("%lu total sectors\n", mbr->parts[3].sec_len);


   for (i=0; i<4; i++) {
      sb = FAT_detect_cb(drive, mbr->parts[i].lba_start);
      if (sb != 0) {
         fsb = (FAT_SuperBlock *) sb;
      }

   }

   sb = (SuperBlock *) fsb;
   return *sb;
}
   
