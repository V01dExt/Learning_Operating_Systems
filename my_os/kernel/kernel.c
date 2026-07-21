#include "idt.h"
#include "timer.h"
#include "pic.h"
#include "keyboard.h"
#include "pmm.h"
#include "vga.h"


void kernel_main()
{
    vga_init();

    vga_print("Kernel Started!\n");

    pmm_init();

    vga_print("PMM Initialization\n");

    void* page1 = pmm_alloc_page();

    vga_print("First allocation: ");
    vga_print_hex((uint32_t)page1);

    pmm_free_page(page1);

    void* page2 = pmm_alloc_page();

    vga_print("\nAfter free: ");
    vga_print_hex((uint32_t)page2);

    idt_init();

    pic_remap();

    timer_init(100);

    keyboard_init();

    __asm__ volatile ("sti");

    while(1)
    {
    }
}
