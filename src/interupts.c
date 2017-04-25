#include "interupts.h"

inline int are_interupts_enabled() {
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}

inline void CLI() {
	asm volatile ("CLI");
}

inline void STI() {
	asm  volatile ("STI");
}
