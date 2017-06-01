#ifndef PRINTK
#define PRINTK

extern int printk(const char *fmt, ...)__attribute__((format (printf, 1, 2)));

#endif
