#include "block_device.h"
#include "kmalloc.h"
#include <stdint-gcc.h>

typedef struct ATABlockDev{
   struct BlockDev dev;
   uint16_t ata_base, ata_master;
   uint8_t slave, irq;
   /*struct ATARequest *req_head, *req_tail;*/
} ATABlockDev;

#define ATA_PRIMARY_BASE 0x1F0
#define ATA_PRIMARY_CONTROL 0x3F6
#define ATA_PRIMARY_IRQ 14
#define ATA_SECONDARY_BASE 0x170
#define ATA_SECONDARY_CONTROL 0x376
#define ATA_SECONDARY_IRQ 15

#define ATA_DRIVE_SELECT_OFFSET 6
#define ATA_SECTOR_COUNT_OFFSET 2
#define ATA_LBALO_OFFSET 3
#define ATA_LBAMID_OFFSET 4
#define ATA_LBAHI_OFFSET 5
#define ATA_COMMAND_IO_OFFSET 7
#define ATA_IDENTIFY 0xEC


int ata_read_block(BlockDev *a, uint64_t blk_num, void *dst) {
   ATABlockDev *this = (ATABlockDev *) a;

   outb(this->ata_base + ATA_DRIVE_SELECT_OFFSET, 0x40 | (this->slave) <<4);

}


BlockDev *probe_ata(uint16_t base, uint16_t master, uint8_t slave, uint8_t irq, char *name) {
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
      return -1;
   }

   while (inb(base + ATA_COMMAND_IO_OFFSET) & 0x80) {
   }

   resp = inb(base + ATA_LBAMID_OFFSET);
   if( resp != 0) {
      return -1;
   }

   resp = inb(base + ATA_LBAHI_OFFSET);
   if (resp != 0) {
      return -1;
   }

   while (!(resp = inb(base + ATA_COMMAND_IO_OFFSET) & 8) && !(resp & 1)) {};

   if (resp & 1) {
      /*ATAPI or SATA*/
      resp = inb(base + ATA_LBAMID_OFFSET);
      resp2 = inb(base + ATA_LBAHI_OFFSET);

      if (resp == 0x14 && resp2 == 0xEB) {
         printk("ATAPI drive unsupported\n");
         return -1;
         /*ATAPI*/
      }

      if (resp == 0x3c && resp2 == 0xc3) {
         printk("SATA drive unsupported\n");
         return -1;
         /*SATA*/
      }
   }

   for (i = 0; i < 256; i++) {
      buff[i] = inw(base);
   }

   if (! (buff[83] & (1 <<10))) {
      /*LBA48 not supported*/
      return -1;
   }

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

void ata_init() {
   BlockDev *dev = probe_ata(ATA_PRIMARY_BASE, ATA_SECONDARY_CONTROL, 0, ATA_PRIMARY_IRQ, "test");
   
}
