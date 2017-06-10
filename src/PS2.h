#ifndef PS2
#define PS2

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
void print_char(char c);
char convert_code(uint8_t);

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);

uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t val);

#endif
