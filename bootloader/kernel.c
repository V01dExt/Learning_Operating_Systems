#include "idt.h"
#include "timer.h"
#include "pic.h"
#include "keyboard.h"

void kernel_main()
{
    idt_init();

    pic_remap();

    timer_init(100);

    keyboard_init();

    __asm__ volatile ("sti");

    while(1)
    {
    }
}