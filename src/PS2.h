#include <stdint-gcc.h>

#define FIRST_INTERUPT (1<<0)
#define SECOND_INTERUPT (1<<1)
#define FIRST_CLOCK (1<<4)
#define SECOND_CLOCK (1<<5)

#define OUT_STATUS (1<<0)
#define IN_STATUS (1<<1)

#define CMD 0x64
#define DATA 0x60

void initialize_ps2();
void initialize_keyboard();
void read_and_print();

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
