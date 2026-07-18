disk_load:
    pusha

    mov ah, 0x02      
    mov al, 9         
    mov ch, 0        
    mov cl, 2         
    mov dh, 0       
    mov dl, [BOOT_DRIVE]

    int 0x13
    jc disk_error

    popa
    ret

disk_error:
    jmp $