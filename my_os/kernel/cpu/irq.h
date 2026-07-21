#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>
#include "registers.h"


typedef void (*irq_handler_t)(struct registers* regs);

void irq_install_handler(uint8_t irq, irq_handler_t handler);
void irq_handler(struct registers* regs);

#endif