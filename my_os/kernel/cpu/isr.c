#include <stdint.h>
#include "isr.h"
#include "registers.h"



void isr_handler(struct registers* regs)
{
    volatile char* video = (volatile char*)0xb8000;

    video[6] = 'I';
    video[7] = 0x07;

    while(1)
    {
    }
}