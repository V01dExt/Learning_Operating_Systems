[BITS 16]
[ORG 0x7C00]

start:
    xor ax, ax
    mov ds, ax      
    mov es, ax        
    mov ss, ax
    mov sp, 0x7C00  
    
    mov [boot_drive], dl
    mov si, msg         

print_loop:
    lodsb
    or al, al
    jz load_kernel
    mov ah, 0x0E
    int 0x10
    jmp print_loop

load_kernel:

    xor ax, ax
    int 0x13
    
    xor ax, ax
    mov es, ax
    mov bx, 0x1000        
    
    mov ah, 0x02       
    mov al, 0x01       
    mov ch, 0x00        
    mov dh, 0x00         
    mov cl, 0x02        
    mov dl, [boot_drive]
    int 0x13
    
    jc disk_error       
    
    jmp 0x0000:0x1000   

disk_error:
    mov si, error_msg
    jmp print_loop     

msg: db "Loading...", 0
error_msg: db " Error!", 0
boot_drive: db 0

times 510 - ($ - $$) db 0
dw 0xAA55
