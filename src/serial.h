#ifndef SERIAL
#define SERIAL

#include "PS2.h"
void serial_setup();
void serial_write_char(char);
void serial_write(char *, int);
void serial_interrupt(void *);

#endif
