#include "idt_setup.h"

static inline void LIDT(uint16_t limit, void *addr) {
   struct {
      uint16_t limit;
      void *addr;
   }__attribute__((packed)) IDTR = {limit, addr};
   asm ("lidt %0" :: "m"(IDTR));
}

uint64_t asm_irq_handler_table[256] = {
(uint64_t) irq0_handler, (uint64_t) irq1_handler, (uint64_t) irq2_handler, (uint64_t) irq3_handler, (uint64_t) irq4_handler, (uint64_t) irq5_handler, (uint64_t) irq6_handler, (uint64_t) irq7_handler, (uint64_t) irq8_handler, (uint64_t) irq9_handler, (uint64_t) irq10_handler, (uint64_t) irq11_handler, (uint64_t) irq12_handler, (uint64_t) irq13_handler, (uint64_t) irq14_handler, (uint64_t) irq15_handler, (uint64_t) irq16_handler, (uint64_t) irq17_handler, (uint64_t) irq18_handler, (uint64_t) irq19_handler, (uint64_t) irq20_handler, (uint64_t) irq21_handler, (uint64_t) irq22_handler, (uint64_t) irq23_handler, (uint64_t) irq24_handler, (uint64_t) irq25_handler, (uint64_t) irq26_handler, (uint64_t) irq27_handler, (uint64_t) irq28_handler, (uint64_t) irq29_handler, (uint64_t) irq30_handler, (uint64_t) irq31_handler, (uint64_t) irq32_handler, (uint64_t) irq33_handler, (uint64_t) irq34_handler, (uint64_t) irq35_handler, (uint64_t) irq36_handler, (uint64_t) irq37_handler, (uint64_t) irq38_handler, (uint64_t) irq39_handler, (uint64_t) irq40_handler, (uint64_t) irq41_handler, (uint64_t) irq42_handler, (uint64_t) irq43_handler, (uint64_t) irq44_handler, (uint64_t) irq45_handler, (uint64_t) irq46_handler, (uint64_t) irq47_handler, (uint64_t) irq48_handler, (uint64_t) irq49_handler, (uint64_t) irq50_handler, (uint64_t) irq51_handler, (uint64_t) irq52_handler, (uint64_t) irq53_handler, (uint64_t) irq54_handler, (uint64_t) irq55_handler, (uint64_t) irq56_handler, (uint64_t) irq57_handler, (uint64_t) irq58_handler, (uint64_t) irq59_handler, (uint64_t) irq60_handler, (uint64_t) irq61_handler, (uint64_t) irq62_handler, (uint64_t) irq63_handler, (uint64_t) irq64_handler, (uint64_t) irq65_handler, (uint64_t) irq66_handler, (uint64_t) irq67_handler, (uint64_t) irq68_handler, (uint64_t) irq69_handler, (uint64_t) irq70_handler, (uint64_t) irq71_handler, (uint64_t) irq72_handler, (uint64_t) irq73_handler, (uint64_t) irq74_handler, (uint64_t) irq75_handler, (uint64_t) irq76_handler, (uint64_t) irq77_handler, (uint64_t) irq78_handler, (uint64_t) irq79_handler, (uint64_t) irq80_handler, (uint64_t) irq81_handler, (uint64_t) irq82_handler, (uint64_t) irq83_handler, (uint64_t) irq84_handler, (uint64_t) irq85_handler, (uint64_t) irq86_handler, (uint64_t) irq87_handler, (uint64_t) irq88_handler, (uint64_t) irq89_handler, (uint64_t) irq90_handler, (uint64_t) irq91_handler, (uint64_t) irq92_handler, (uint64_t) irq93_handler, (uint64_t) irq94_handler, (uint64_t) irq95_handler, (uint64_t) irq96_handler, (uint64_t) irq97_handler, (uint64_t) irq98_handler, (uint64_t) irq99_handler, (uint64_t) irq100_handler, (uint64_t) irq101_handler, (uint64_t) irq102_handler, (uint64_t) irq103_handler, (uint64_t) irq104_handler, (uint64_t) irq105_handler, (uint64_t) irq106_handler, (uint64_t) irq107_handler, (uint64_t) irq108_handler, (uint64_t) irq109_handler, (uint64_t) irq110_handler, (uint64_t) irq111_handler, (uint64_t) irq112_handler, (uint64_t) irq113_handler, (uint64_t) irq114_handler, (uint64_t) irq115_handler, (uint64_t) irq116_handler, (uint64_t) irq117_handler, (uint64_t) irq118_handler, (uint64_t) irq119_handler, (uint64_t) irq120_handler, (uint64_t) irq121_handler, (uint64_t) irq122_handler, (uint64_t) irq123_handler, (uint64_t) irq124_handler, (uint64_t) irq125_handler, (uint64_t) irq126_handler, (uint64_t) irq127_handler, (uint64_t) irq128_handler, (uint64_t) irq129_handler, (uint64_t) irq130_handler, (uint64_t) irq131_handler, (uint64_t) irq132_handler, (uint64_t) irq133_handler, (uint64_t) irq134_handler, (uint64_t) irq135_handler, (uint64_t) irq136_handler, (uint64_t) irq137_handler, (uint64_t) irq138_handler, (uint64_t) irq139_handler, (uint64_t) irq140_handler, (uint64_t) irq141_handler, (uint64_t) irq142_handler, (uint64_t) irq143_handler, (uint64_t) irq144_handler, (uint64_t) irq145_handler, (uint64_t) irq146_handler, (uint64_t) irq147_handler, (uint64_t) irq148_handler, (uint64_t) irq149_handler, (uint64_t) irq150_handler, (uint64_t) irq151_handler, (uint64_t) irq152_handler, (uint64_t) irq153_handler, (uint64_t) irq154_handler, (uint64_t) irq155_handler, (uint64_t) irq156_handler, (uint64_t) irq157_handler, (uint64_t) irq158_handler, (uint64_t) irq159_handler, (uint64_t) irq160_handler, (uint64_t) irq161_handler, (uint64_t) irq162_handler, (uint64_t) irq163_handler, (uint64_t) irq164_handler, (uint64_t) irq165_handler, (uint64_t) irq166_handler, (uint64_t) irq167_handler, (uint64_t) irq168_handler, (uint64_t) irq169_handler, (uint64_t) irq170_handler, (uint64_t) irq171_handler, (uint64_t) irq172_handler, (uint64_t) irq173_handler, (uint64_t) irq174_handler, (uint64_t) irq175_handler, (uint64_t) irq176_handler, (uint64_t) irq177_handler, (uint64_t) irq178_handler, (uint64_t) irq179_handler, (uint64_t) irq180_handler, (uint64_t) irq181_handler, (uint64_t) irq182_handler, (uint64_t) irq183_handler, (uint64_t) irq184_handler, (uint64_t) irq185_handler, (uint64_t) irq186_handler, (uint64_t) irq187_handler, (uint64_t) irq188_handler, (uint64_t) irq189_handler, (uint64_t) irq190_handler, (uint64_t) irq191_handler, (uint64_t) irq192_handler, (uint64_t) irq193_handler, (uint64_t) irq194_handler, (uint64_t) irq195_handler, (uint64_t) irq196_handler, (uint64_t) irq197_handler, (uint64_t) irq198_handler, (uint64_t) irq199_handler, (uint64_t) irq200_handler, (uint64_t) irq201_handler, (uint64_t) irq202_handler, (uint64_t) irq203_handler, (uint64_t) irq204_handler, (uint64_t) irq205_handler, (uint64_t) irq206_handler, (uint64_t) irq207_handler, (uint64_t) irq208_handler, (uint64_t) irq209_handler, (uint64_t) irq210_handler, (uint64_t) irq211_handler, (uint64_t) irq212_handler, (uint64_t) irq213_handler, (uint64_t) irq214_handler, (uint64_t) irq215_handler, (uint64_t) irq216_handler, (uint64_t) irq217_handler, (uint64_t) irq218_handler, (uint64_t) irq219_handler, (uint64_t) irq220_handler, (uint64_t) irq221_handler, (uint64_t) irq222_handler, (uint64_t) irq223_handler, (uint64_t) irq224_handler, (uint64_t) irq225_handler, (uint64_t) irq226_handler, (uint64_t) irq227_handler, (uint64_t) irq228_handler, (uint64_t) irq229_handler, (uint64_t) irq230_handler, (uint64_t) irq231_handler, (uint64_t) irq232_handler, (uint64_t) irq233_handler, (uint64_t) irq234_handler, (uint64_t) irq235_handler, (uint64_t) irq236_handler, (uint64_t) irq237_handler, (uint64_t) irq238_handler, (uint64_t) irq239_handler, (uint64_t) irq240_handler, (uint64_t) irq241_handler, (uint64_t) irq242_handler, (uint64_t) irq243_handler, (uint64_t) irq244_handler, (uint64_t) irq245_handler, (uint64_t) irq246_handler, (uint64_t) irq247_handler, (uint64_t) irq248_handler, (uint64_t) irq249_handler, (uint64_t) irq250_handler, (uint64_t) irq251_handler, (uint64_t) irq252_handler, (uint64_t) irq253_handler, (uint64_t) irq254_handler, (uint64_t) irq255_handler,
};

char gp_tss[4096];
char df_tss[4096];
char pf_tss[4096];
char exit_tss[4096];

/*initializes the pic to 0x20-0x2F*/
void PIC_setup() {
   unsigned char mask1, mask2;

   /*save masks*/
   mask1 = inb(PIC1_DATA);
   mask2 = inb(PIC2_DATA);
   
   /*start initialization*/
   outb(PIC1, PIC_INITIALIZATION);
   /*io_wait();*/
   outb(PIC2, PIC_INITIALIZATION);
   /*io_wait();*/

   /*set offsets*/
   outb(PIC1_DATA, 0x20);
   /*io_wait();*/
   outb(PIC2_DATA, 0x28);
   /*io_wait();*/

   /*wiring*/
   outb(PIC1_DATA, 4);
   /*io_wait();*/
   outb(PIC2_DATA, 2);
   /*io_wait();*/

   /*environment*/
   outb(PIC1_DATA, 1);
   /*io_wait();*/
   outb(PIC2_DATA, 1);
   /*io_wait();*/

   /*restore masks*/
   outb(PIC1_DATA, mask1);
   outb(PIC2_DATA, mask2);
}

void idt_test() {
   printk("idt_test\n");
   while(1) {};
}

typedef struct tss {
   uint32_t ign;
   uint64_t RSP0;
   uint64_t RSP1;
   uint64_t RSP2;
   uint64_t ign_2;
   uint64_t IST1;
   uint64_t IST2;
   uint64_t IST3;
   uint64_t IST4;
   uint64_t IST5;
   uint64_t IST6;
   uint64_t IST7;
   uint64_t ign_3;
   uint16_t ign_4;
   uint16_t io_base_addr;
}__attribute__((packed)) tss;

tss TSS;

typedef struct tss_descriptor {
   uint16_t segment_limit;
   uint16_t base_addr_1;
   uint8_t base_addr_2;
   uint8_t Type:4;
   uint8_t pad:1;
   uint8_t dpl:2;
   uint8_t P:1;
   uint8_t segment_limit_2:4;
   uint8_t AVL:1;
   uint8_t res:2;
   uint8_t G:1;
   uint8_t base_addr_3;
   uint32_t base_addr_4;
   uint32_t res2:8;
   uint32_t zeros:5;
   uint32_t res3:19;
}__attribute__((packed)) tss_descriptor;

typedef struct gdt_entry{
   uint64_t entry;
}__attribute__((packed)) gdt_entry;

extern uint64_t gdt64[2];

typedef struct gdt_representation{
   uint16_t size;
   uint64_t ptr;
}__attribute__((packed)) gdt_representation;

void tss_setup() {
   tss_descriptor *TSS_descriptor;
   uint64_t mask1 = 0xFFFF;
   uint64_t mask2 = 0xFF0000;
   uint64_t mask3 = 0xFF000000;
   uint64_t mask4 = 0xFFFFFFFF00000000;
   uint16_t selector;
   int k = 1;

   TSS.IST1 = ((uint64_t)&gp_tss) + 4096 - 1;
   TSS.IST2 = ((uint64_t)&df_tss) + 4096 - 1;
   TSS.IST3 = ((uint64_t)&pf_tss) + 4096 - 1;
   TSS.IST4 = ((uint64_t)&exit_tss) + 4096 - 1;
   TSS.ign = 0;
   TSS.RSP0 = 0;
   TSS.RSP1 = 0;
   TSS.RSP2 = 0;
   TSS.ign_2 = 0;

   TSS_descriptor = gdt64 + 2;

   TSS_descriptor->base_addr_1 = ((uint64_t)(&TSS)) & mask1;
   TSS_descriptor->base_addr_2 = (((uint64_t)(&TSS)) & mask2) >> 16;
   TSS_descriptor->base_addr_3 = (((uint64_t)(&TSS)) & mask3) >> 24;
   TSS_descriptor->base_addr_4 = (((uint64_t)(&TSS)) & mask4) >> 32;

   TSS_descriptor->zeros = 0;
   TSS_descriptor->G = 0; /*limit is in bytes*/
   TSS_descriptor->P = 1;
   TSS_descriptor->dpl = 0;
   TSS_descriptor->pad = 0;
   TSS_descriptor->Type = 9; /*not busy*/
   
   TSS_descriptor->segment_limit = sizeof(tss) & 0xFFFF;
   TSS_descriptor->segment_limit_2 = (sizeof(tss) & 0xF0000) >>16;


   selector = 0x10;
   asm("ltr %0" ::"m"(selector));
}

void idt_setup() {
   uint64_t ptr;
   uint64_t end_mask = 0xFFFF;
   uint64_t mid_mask = 0xFFFF0000;
   uint64_t start_mask = 0xFFFFFFFF00000000;
   uint16_t length = sizeof(IDT_entry) * 256;
   int i;
   for(i = 0; i < 256; i++) {
      IDT_table[i].IST = 0;
      IDT_table[i].type = 0xE; /*interrupt gate*/
      IDT_table[i].buf = 0;
      IDT_table[i].DPL = 0; /*protection level*/
      IDT_table[i].P = 1;

      IDT_table[i].target_selector = 0x08; /*kernel code segment*/
      ptr = asm_irq_handler_table[i];
      /*ptr = (uint64_t) idt_test;*/
      IDT_table[i].start_target_offset = (start_mask & ptr) >>32;
      IDT_table[i].mid_target_offset = (mid_mask & ptr) >>16;
      IDT_table[i].end_target_offset = end_mask & ptr;

      /*GP*/
      if (i == 13) {
         IDT_table[i].IST = 1;
      }
      /*df*/
      if (i == 8) {
         IDT_table[i].IST = 2;
      }
      /*pf*/
      if (i == 14) {
         IDT_table[i].IST = 3;
      }
      /*exit*/
      if (i == 0x7C) {
         IDT_table[i].IST = 4;
      }
   }

   tss_setup();

   LIDT(length, IDT_table);
}

/*this masks all for now*/
void IRQ_set_all_masks() {
   int i;
   uint16_t port;
   uint8_t value;

   for(i=0; i<8; i++) {
      if (i != 2) {
         port = PIC1_DATA;
         value = inb(port) | 0xFF;
         outb(port, value);
      }
      port = PIC2_DATA;
      value = inb(port) | 0xFF;
      outb(port, value);
   }
}

void IRQ_set_mask(unsigned char num) {
   uint16_t port;
   uint8_t value;

   if (num < 8) {
      port = PIC1_DATA;
   }
   else {
      port = PIC2_DATA;
      num -= 8;
   }

   value = inb(port) | (1 << num);
   outb(port, value);
}

void IRQ_clear_mask(unsigned char num) {
   uint16_t port;
   uint8_t value;

   if (num < 8) {
      port = PIC1_DATA;
   }
   else {
      port = PIC2_DATA;
      num -= 8;
   }

   value = inb(port) & ~(1 << num);
   outb(port, value);
}

uint16_t pic_get_irr() {
   outb(PIC1, 0x0a);
   outb(PIC2, 0x0a);
   return (inb(PIC2) << 8) | inb(PIC1);
}

uint16_t pic_get_isr() {
   outb(PIC1, 0x0b);
   outb(PIC2, 0x0b);
   return (inb(PIC2) << 8) | inb(PIC1);
}

void IRQ_end_of_interrupt(int irq) {
   if(irq < 8) {
      outb(PIC2, 0x20);
   }
   outb(PIC1, 0x20);
}
