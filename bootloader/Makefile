KERNEL_ENTRY = kernel_entry.o
KERNEL_OBJ = kernel.o
KERNEL_BIN = kernel.bin
MBR_BIN = mbr.bin
OS_IMAGE = os_image.bin

CC = gcc
LD = C:/i686-elf/bin/ld.exe
NASM = nasm
QEMU = "C:/Program Files/qemu/qemu-system-i386.exe"

CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector

all: $(OS_IMAGE)

$(KERNEL_BIN): $(KERNEL_ENTRY) $(KERNEL_OBJ)
	$(LD) -m elf_i386 -Ttext 0x1000 $(KERNEL_ENTRY) $(KERNEL_OBJ) --oformat binary -o $(KERNEL_BIN)

kernel_entry.o: kernel_entry.asm
	$(NASM) kernel_entry.asm -f elf -o kernel_entry.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

$(MBR_BIN): MBR.asm
	$(NASM) MBR.asm -f bin -o mbr.bin

$(OS_IMAGE): $(MBR_BIN) $(KERNEL_BIN)
	copy /b mbr.bin+kernel.bin os_image.bin

run: $(OS_IMAGE)
	$(QEMU) -fda os_image.bin -boot a

clean:
	del *.o
	del *.bin