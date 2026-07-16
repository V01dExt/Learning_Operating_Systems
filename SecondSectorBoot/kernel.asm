[BITS 16]
[ORG 0x1000]

start:
    mov ax, 0x0000
    mov si, kernel_msg

print_loop:
    lodsb
    or al, al
    jz halt
    mov ah, 0x0E
    int 0x10
    jmp print_loop

halt: 
    cli
    hlt

kernel_msg: db "Kernel Loaded!", 0

times 510 - ($ - $$) db 0
dw 0xAA55
