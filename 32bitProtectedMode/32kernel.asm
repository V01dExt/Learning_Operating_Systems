[BITS 32]
[ORG 0x1000]

start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x90000

    mov edi, 0xB8000
    mov ax, 0x0F00 | 'P'
    mov [edi], ax
    mov ax, 0x0A00 | 'M'
    mov [edi + 2], ax

    cli
    hlt

times 512 - ($ - $$) db 0
