#include "timer.h"
#include "io.h"
#include "irq.h"
#include "vga.h"


static uint32_t ticks = 0;


void timer_callback(struct registers* regs)
{
    ticks++;

    vga_put_char('T');
}


void timer_init(uint32_t frequency) {

    uint32_t divisor = 1193180 / frequency;


    outb(0x43, 0x36);

    outb(0x40, (uint8_t)(divisor & 0xFF));
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));


    irq_install_handler(0, timer_callback);
}