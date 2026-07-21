[BITS 32]

global irq0
global irq1

extern irq_handler


irq0:
    cli
    push 0
    push 32
    jmp irq_common


irq1:
    cli
    push 0
    push 33
    jmp irq_common


irq_common:

    push ds

    pusha

    mov ax, 0x10
    mov ds, ax
    mov es, ax

    push esp
    call irq_handler
    add esp, 4

    popa

    pop ds

    add esp, 8

    sti
    iretd