#ifndef ATA_DRIVER
#define ATA_DRIVER

#include "block_device.h"
#include "PS2.h"
#include "kmalloc.h"
#include <stdint-gcc.h>
#include "context_swap.h"
#include "interrupts.h"
#include "idt_setup.h"
#include "types.h"

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

void ata_isr(uint64_t irq, uint64_t err);

int ata_read_block(BlockDev *a, uint64_t blk_num, void *dst);

ATABlockDev *ata_init();

typedef struct ReadQueue {
   ATABlockDev *dev;
   void *dst;
   uint64_t lba;
   struct ReadQueue *next;
} ReadQueue;

#endif
