#ifndef CONTEXT_SWAP
#define CONTEXT_SWAP

#include <stdint-gcc.h>
#include "interrupts.h"
#include "kmalloc.h"
#include "virtual_allocation.h"

#define INTERRUPTS_ENABLED 512
/* IMPORTANT: do not change the order of these registers!!!
 * Add anything new to the bottom of the struct*/
typedef struct Process{
   uint64_t r15;
   uint64_t r14;
   uint64_t r13;
   uint64_t r12;
   uint64_t r11;
   uint64_t r10;
   uint64_t r9;
   uint64_t r8;
   uint64_t rdx;
   uint64_t rcx;
   uint64_t rbx;
   uint64_t rax;
   uint64_t rbp;
   uint64_t rsi;
   uint64_t rdi;

   uint64_t rip;
   uint64_t cs;
   uint64_t rflags;
   uint64_t rsp;
   uint64_t ss;

   uint64_t ds;
   uint64_t es;

   uint64_t pid;
   uint64_t CR3;
   struct Process *next;
   struct Process *sched_next;
}__attribute__((packed)) Process;

extern Process *cur_proc;
extern Process *next_proc;

void kexit();

typedef void (*kproc_t)(void*);

Process *PROC_create_kthread(kproc_t entry_point, void *arg);
void PROC_reschedule();
void yield();
void yield_isr();
void PROC_run();
void exit_isr(void *irq, void *err);

typedef struct ProcessQueue {
   Process *proc;
   struct ProcessQueue *next;
} ProcessQueue;

void PROC_block_on(ProcessQueue**, int enable_ints);
void PROC_unblock_head(ProcessQueue**);
void PROC_unblock_all(ProcessQueue**);


#endif
