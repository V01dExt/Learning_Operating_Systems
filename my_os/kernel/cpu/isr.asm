[BITS 32]

global isr0

extern isr_handler

isr0:
    cli

    push ds

    pusha

    push 0          
    push 0          

    mov eax, esp
    push eax

    call isr_handler

    add esp, 4

    popa

    pop ds

    add esp, 8

    sti
    iret
