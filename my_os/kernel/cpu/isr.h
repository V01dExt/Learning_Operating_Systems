#ifndef ISR_H
#define ISR_H

#include <stdint.h>

struct registers;

void isr_handler(struct registers* regs);


#endif