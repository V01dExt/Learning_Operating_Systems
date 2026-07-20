[BITS 16]
[org 0x7C00]


KERNEL_OFFSET equ 0x1000


mov [BOOT_DRIVE], dl
mov bp, 0x8000
mov sp, bp

call load_kernel
call switch_to_32bit

jmp $

%include "disk.asm"
%include "gdt.asm"
%include "32bitmode.asm"


[BITS 16]

load_kernel:
    mov bx, KERNEL_OFFSET

    mov dl, [BOOT_DRIVE]

    mov ax, 0x0000
    mov es, ax

    call disk_load
    ret

[BITS 32]

BEGIN_32BIT:
    call KERNEL_OFFSET
    jmp $


BOOT_DRIVE db 0

times 510 - ($ - $$) db 0

dw 0xAA55