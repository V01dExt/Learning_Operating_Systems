[BITS 16]
[ORG 0x7C00]

start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    mov [boot_drive], dl

    
    mov dl, [boot_drive]
    mov ah, 0x02       
    mov al, 0x01        
    mov ch, 0x00        
    mov dh, 0x00        
    mov cl, 0x02      
    mov bx, 0x1000      
    mov es, ax          
    int 0x13
    jc disk_error

    call enable_a20
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    
    jmp 0x08:0x1000

disk_error:
    mov si, error_msg
    jmp print_loop

enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

print_loop:
    lodsb
    or al, al
    jz $
    mov ah, 0x0E
    int 0x10
    jmp print_loop

gdt_start:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

msg:        db "Loading...", 0
error_msg:  db " Error!", 0
boot_drive: db 0

times 510 - ($ - $$) db 0
dw 0xAA55
