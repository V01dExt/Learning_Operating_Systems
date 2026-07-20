[BITS 32]

global _start
extern kernel_main

_start:
    mov byte [0xb8000], '1'
    mov byte [0xb8001], 0x07

    call kernel_main

hang:
    cli
    hlt
    jmp hang