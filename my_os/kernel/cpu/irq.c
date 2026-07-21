#include "irq.h"
#include "pic.h"


static irq_handler_t irq_routines[16];


void irq_install_handler(uint8_t irq, irq_handler_t handler) {

    irq_routines[irq] = handler;
}


void irq_handler(struct registers* regs)
{
    uint8_t irq = regs->int_no - 32;

    volatile char* video = (volatile char*)0xb8000;

    if (irq == 1)
    {
        video[30] = '1';
        video[31] = 0x07;
    }

    if (irq < 16 && irq_routines[irq])
    {
        irq_routines[irq](regs);
    }

    pic_send_eoi(irq);
}