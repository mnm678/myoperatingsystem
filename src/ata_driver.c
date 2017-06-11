#include "ata_driver.h"

ProcessQueue *ata_blocked =0;
ReadQueue *ata_read_head = 0;

void ata_handler(int read) {
   int i;
   int k=1;
   ReadQueue *temp;
   uint8_t resp = inb(ATA_PRIMARY_BASE + ATA_COMMAND_IO_OFFSET);
   uint64_t mask;
   uint8_t cur;
   uint16_t sectorcount = 1;
   uint64_t LBA;
   ATABlockDev *this;
   int sectorSize = 256;
   
   if (ata_read_head && !read && (resp & 8)) {
      /*read*/
      this = ata_read_head->dev;
      for(i=0; i < sectorSize; i++) {
         ((uint16_t *)ata_read_head->dst)[i] = inw(this->ata_base);
      }

      temp = ata_read_head;
      ata_read_head = ata_read_head->next;
      kfree(temp);
      read = 1;
   }
   
   if (ata_read_head && read) {

      /*set up read*/
      LBA = ata_read_head->lba;
      this = ata_read_head->dev;

      outb(this->ata_base + ATA_DRIVE_SELECT_OFFSET, 0x40 | (this->slave) <<4);
      mask = 0xFF;
      cur = ((mask << 8) & sectorcount)>> 8;
      outb(this->ata_base + ATA_SECTOR_COUNT_OFFSET, cur);
      cur = ((mask << 24) & LBA) >> 24;
      outb(this->ata_base + ATA_LBALO_OFFSET, cur);
      cur = ((mask << 32) & LBA) >> 32;
      outb(this->ata_base + ATA_LBAMID_OFFSET, cur);
      cur = ((mask << 40) & LBA) >> 40;
      outb(this->ata_base + ATA_LBAHI_OFFSET, cur);

      cur = mask & sectorcount;
      outb(this->ata_base + ATA_SECTOR_COUNT_OFFSET, cur);
      cur = ((mask << 0) & LBA) >> 0;
      outb(this->ata_base + ATA_LBALO_OFFSET, cur);
      cur = ((mask << 8) & LBA) >> 8;
      outb(this->ata_base + ATA_LBAMID_OFFSET, cur);
      cur = ((mask << 16) & LBA) >> 16;
      outb(this->ata_base + ATA_LBAHI_OFFSET, cur);

      outb(this->ata_base + ATA_COMMAND_IO_OFFSET, 0x24);

      /*polling for testing*/

      /*while(resp = inb(ATA_PRIMARY_BASE + ATA_COMMAND_IO_OFFSET) & 0x80) {};


      for(i=0; i < sectorSize; i++) {
         ((uint16_t *)ata_read_head->dst)[i] = inw(this->ata_base);
      }

      temp = ata_read_head;
      ata_read_head = ata_read_head->next;
      kfree(temp);*/

   }

}


void ata_isr(uint64_t irq, uint64_t err) {
   uint8_t resp;
   int k = 1;
   /*while(k){};*/

   ata_handler(0);

   IRQ_end_of_interrupt(14);

   PROC_unblock_all(&ata_blocked);
}


void ata_add_to_queue(BlockDev *dev, uint64_t lba, void *dst) {
   ReadQueue *temp;
   if (!ata_read_head) {
      ata_read_head = kmalloc(sizeof(ReadQueue));
      ata_read_head->dev = (ATABlockDev*)dev;
      ata_read_head->next = 0;
      ata_read_head->dst = dst;
      ata_read_head->lba = lba;
      return;
   }

   temp = ata_read_head;
   while (temp) {
      if (temp->next == 0) {
         temp->next = kmalloc(sizeof(ReadQueue));
         temp->next->dev = (ATABlockDev*)dev;
         temp->next->lba = lba;
         temp->next->dst = dst;
         temp->next->next = 0;
         return;
      }
      temp = temp->next;
   }
}
      

int ata_read_block(BlockDev *a, uint64_t blk_num, void *dst) {
   ATABlockDev *this = (ATABlockDev *) a;
   int i;
   uint16_t data;
   int k = 1;

   uint64_t LBA = blk_num;

   /*while(k){};*/
   CLI();
   ata_add_to_queue((BlockDev *)this, LBA, dst);

   ata_handler(1);

   PROC_block_on(&ata_blocked, 1);

   k=1;
   /*while(k){};*/
   return blk_num;
}


ATABlockDev *probe_ata(uint16_t base, uint16_t master, uint8_t slave, uint8_t irq, char *name) {
   ATABlockDev *ret;
   int readCnt;
   uint16_t resp;
   uint16_t resp2;
   int i;
   uint16_t buff[256];
   uint64_t numSectors = 0;
   uint32_t sectorsInBlock = 0;
   int k=1;

   /*while(k){};*/
   /*disable interrupts*/
   outb(ATA_PRIMARY_CONTROL, 1);


   /*identify*/
   if(!slave) {
      outb(base + ATA_DRIVE_SELECT_OFFSET, 0xA0);
   }
   else {
      outb(base + ATA_DRIVE_SELECT_OFFSET, 0xB0);
   }

   outb(base + ATA_SECTOR_COUNT_OFFSET, 0);
   outb(base + ATA_LBALO_OFFSET, 0);
   outb(base + ATA_LBAMID_OFFSET, 0);
   outb(base + ATA_LBAHI_OFFSET, 0);

   outb(base + ATA_COMMAND_IO_OFFSET, ATA_IDENTIFY);

   readCnt = 5;
   while(readCnt--) {
      resp = inb(base + ATA_COMMAND_IO_OFFSET);
   }

   if(resp == 0) {
      return ERR_RET;
   }

   while (inb(base + ATA_COMMAND_IO_OFFSET) & 0x80) {
   }

   resp = inb(base + ATA_LBAMID_OFFSET);
   if( resp != 0) {
      return ERR_RET;
   }

   resp = inb(base + ATA_LBAHI_OFFSET);
   if (resp != 0) {
      return ERR_RET;
   }

   while (!(resp = inb(base + ATA_COMMAND_IO_OFFSET) & 8) && !(resp & 1)) {};

   if (resp & 1) {
      /*ATAPI or SATA*/
      resp = inb(base + ATA_LBAMID_OFFSET);
      resp2 = inb(base + ATA_LBAHI_OFFSET);

      if (resp == 0x14 && resp2 == 0xEB) {
         printk("ATAPI drive unsupported\n");
         return ERR_RET;
         /*ATAPI*/
      }

      if (resp == 0x3c && resp2 == 0xc3) {
         printk("SATA drive unsupported\n");
         return ERR_RET;
         /*SATA*/
      }
   }

   for (i = 0; i < 256; i++) {
      buff[i] = inw(base);
   }

   if (! (buff[83] & (1 <<10))) {
      /*LBA48 not supported*/
      return ERR_RET;
   }

   /*allow interrupts*/
   outb(ATA_PRIMARY_CONTROL, 0);

   /*setup struct*/

   ret = kmalloc(sizeof(ATABlockDev));
   ret->ata_base = base;
   ret->ata_master = master;
   ret->slave = slave;
   ret->irq = irq;
   ret->dev.name = name;
   ret->dev.read_block = &ata_read_block;


   return ret;
}

ATABlockDev *ata_init() {
   ATABlockDev *dev = probe_ata(ATA_PRIMARY_BASE, ATA_SECONDARY_CONTROL, 0, ATA_PRIMARY_IRQ, "test");

   IRQ_clear_mask(14);

   return dev;
}
