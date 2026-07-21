#include "vga.h"

static uint16_t* video_memory = (uint16_t*)0xB8000;

static uint16_t cursor = 0;

static uint8_t color = 0x07;


void vga_init(void)
{
    cursor = 0;
    vga_clear();
}


void vga_clear(void)
{
    for(int i = 0; i < 80 * 25; i++)
    {
        video_memory[i] = ((uint16_t)color << 8) | ' ';
    }

    cursor = 0;
}


void vga_put_char(char c)
{
    video_memory[cursor++] = ((uint16_t)color << 8) | c;
}


void vga_print(char* str)
{
    while(*str)
    {
        vga_put_char(*str);
        str++;
    }
}


void vga_print_hex(uint32_t value)
{
    char hex[] = "0123456789ABCDEF";

    vga_print("0x");

    for(int i = 7; i >= 0; i--)
    {
        vga_put_char(hex[(value >> (i * 4)) & 0xF]);
    }
}