#include "idt.h"
#include "io.h"
#include "pic.h"

extern void isr0();

extern void irq0();
extern void irq1();

struct idt_entry idt[256] = {0};
struct idt_ptr idtp = {0};


void idt_set_gate(
    uint8_t num,
    uint32_t base,
    uint16_t selector,
    uint8_t flags
)
{
    idt[num].offset_low = base & 0xFFFF;
    idt[num].offset_high = (base >> 16) & 0xFFFF;

    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].flags = flags;
}


void idt_init(void)
{
    idtp.limit = sizeof(struct idt_entry) * 256 - 1;
    idtp.base = (uint32_t)&idt;

    idt_set_gate(
        0,
        (uint32_t)isr0,
        0x08,
        0x8E
    );

    idt_set_gate(
        32,
        (uint32_t)irq0,
        0x08,
        0x8E
    );

    idt_set_gate(
        33,
        (uint32_t)irq1,
        0x08,
        0x8E
    );

    idt_load();
}