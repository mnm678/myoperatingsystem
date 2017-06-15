#ifndef SYS_CALLS
#define SYS_CALLS
typedef void (*sys_call_func)(void *arg);

void sys_call_test(int unused, int unused2, int sys_call_num, void *arg);

void not_implemented_sys_call(void *);
void putc_impl(void *c);
void getc_impl(void *c);

void putc(char c);

extern sys_call_func sys_impl[30];

#endif
