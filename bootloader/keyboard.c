#include "keyboard.h"
#include "io.h"
#include "irq.h"
#include "registers.h"


static char keyboard_map[128] =
{
    0,  27, '1','2','3','4','5','6','7','8','9','0',
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


static int cursor = 40;


void keyboard_handler(struct registers* regs)
{
    
    volatile char* video = (volatile char*)0xb8000;

    video[20] = 'K';
    video[21] = 0x07;


    uint8_t scancode = inb(0x60);


    // Ignore key release events
    if (scancode & 0x80)
    {
        return;
    }


    char c = keyboard_map[scancode];


    if (c)
    {
        video[cursor] = c;
        video[cursor + 1] = 0x07;

        cursor += 2;
    }
}


void keyboard_init(void)
{
    irq_install_handler(1, keyboard_handler);
}