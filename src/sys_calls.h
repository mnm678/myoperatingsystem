#ifndef SYS_CALLS
#define SYS_CALLS
typedef void (*sys_call_func)();

void not_implemented_sys_call();

sys_call_func sys_impl[30] = {
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
   not_implemented_sys_call,
   not_implemented_sys_call,
   not_implemented_sys_call
};
#endif
