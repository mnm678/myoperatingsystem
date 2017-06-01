#include "context_swap.h"

Process *cur_proc = 0;
Process *next_proc = 0;

void kexit() {
   asm( "int $0x7C");
}

Process *proc_head = 0;
Process *sched_head = 0;
int proc_num = 0;

Process *PROC_create_kthread(kproc_t entry_point, void *arg) {
   int k=1;
   Process *proc = kmalloc(sizeof(Process));
   Process *temp;

   proc->r8 = proc->r9 = proc->r10 = proc->r11 = proc->r12 = 0;
   proc->r13 = proc->r14 = proc->r15 = 0;
   proc->rdx = proc->rcx = proc->rbx = proc->rax = proc->rbp = proc->rsi=0;

   proc->rdi = (uint64_t)arg;
   proc->rip = (uint64_t)entry_point;
   proc->cs = 0x8; /*kernel code segment*/
   proc->rflags = INTERRUPTS_ENABLED;
   proc->rsp = (uint64_t)add_kstack();
   proc->ss = proc->ds = proc->es = 0;
   proc->next = proc->sched_next = 0;

   /*while(k){};*/

   proc->pid = proc_num++;
   *((uint64_t*)(proc->rsp))=(uint64_t)&kexit;
   proc->rsp--;

   /*add proc to linked list*/
   if (!proc_head) {
      proc_head = proc;
   }
   else {
      temp = proc_head;
      while(temp) {
         if (temp->next) {
            temp = temp->next;
         }
         else {
            temp->next = proc;
            temp = 0;
         }
      }
   }
   
   /*schedule list*/
   if (!sched_head) {
      sched_head = proc;
   }
   else{
      temp = sched_head;
      while(temp) {
         if (temp->sched_next) {
            temp = temp->sched_next;
         }
         else {
            temp->sched_next = proc;
            temp = 0;
         }
      }
   }

   return proc;
}


struct Process *mainProcPtr = 0;
void PROC_reschedule() {
   Process *temp;

   int interrupts = are_interrupts_enabled();

   if (interrupts) {
      CLI();
   }

   if (!sched_head) {
      next_proc = mainProcPtr;
      return;
   }
   next_proc = sched_head;

   sched_head = sched_head->sched_next;

   temp = sched_head;
   /* one or 2 elements in sched_head?*/
   while (temp) {
      if (!temp->sched_next) {
         if (cur_proc != mainProcPtr) {
            temp->sched_next = cur_proc;
            temp->sched_next->sched_next = 0;
         }
         temp = 0;
      }
      else {
         temp = temp->sched_next;
      }
   }

   if (interrupts) {
      STI();
   }
}

void yield() {
   asm( "int $0x7B");
}

void yield_isr() {
   int k = 1;
   /*while(k){};*/
   PROC_reschedule();
}

void PROC_run() {
   struct Process mainProc;
   mainProcPtr = &mainProc;
   cur_proc = &mainProc;
   yield();
}


void exit_isr(void *irq, void *err) {
   Process *temp;
   int k = 1;
   while(k){};
   printk("exit_isr\n");

   /*remove cur_proc from linked list*/
   temp = sched_head;
   if(temp == cur_proc) {
      sched_head = sched_head->sched_next;
      temp = sched_head;
   }
   else {
      while(temp) {
         if (temp->sched_next && temp->sched_next == cur_proc) {
            cur_proc->sched_next = cur_proc->sched_next->sched_next;
         }
         temp = temp->sched_next;
      }
   }

   temp = proc_head;
   if (temp == cur_proc) {
      proc_head = proc_head->next;
      temp = proc_head;
   }
   else {
      while(temp) {
         if (temp->next && temp->next==cur_proc) {
            cur_proc->next = cur_proc->next->next;
         }
         temp = temp->next;
      }
   }

   /*to prevent this process being rescheduled*/
   cur_proc = mainProcPtr;

   PROC_reschedule();

   /*TODO free stack*/
   /*TODO user space: free page table*/
   kfree(cur_proc);
}

