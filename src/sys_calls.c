#include "sys_calls.h"
#include "printk.h"
#include "keyboard_driver.h"

sys_call_func sys_impl[30] = {
   putc_impl,
   getc_impl,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call
};

void sys_call_test(int unused, int unused2, int sys_call_num, void *arg) {
   asm("int $0x80");
}


void not_implemented_sys_call(void *arg) {
   printk("not implemented sys call\n");
}

void putc_impl(void *arg) {
   char c[2];
   c[0]= (char) arg;
   c[1] = 0;
   printk(&c);
}

void getc_impl(void *arg) {
   char *c = (char *)arg;
   KBD_read_char(c);
}


void putc(char c) {
   sys_call_test(-1, c, 0, c);
}

char getc() {
   char c;
   sys_call_test(-1, &c, 1, &c);
   return c;
}
