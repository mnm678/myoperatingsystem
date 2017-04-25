#ifndef SERIAL
#define SERIAL

#include "PS2.h"
void serial_setup();
void serial_write_char(char);
void serial_interupt(void *);

#endif
