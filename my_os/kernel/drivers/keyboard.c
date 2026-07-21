#include "keyboard.h"
#include "io.h"
#include "irq.h"
#include "registers.h"
#include "vga.h"


static char keyboard_map[128] =
{
    0, 27, '1','2','3','4','5','6','7','8','9','0',
    '-', '=', '\b',
    '\t',
    'q','w','e','r','t','y','u','i','o','p',
    '[',']','\n',
    0,
    'a','s','d','f','g','h','j','k','l',
    ';','\'','`',
    0,
    '\\',
    'z','x','c','v','b','n','m',
    ',','.','/',
    0,
    '*',
    0,
    ' '
};


void keyboard_handler(struct registers* regs)
{
    uint8_t scancode = inb(0x60);


    
    if (scancode & 0x80)
    {
        return;
    }


    char c = keyboard_map[scancode];


    if (c)
    {
        vga_put_char(c);
    }
}


void keyboard_init(void)
{
    irq_install_handler(1, keyboard_handler);
}