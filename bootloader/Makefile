KERNEL_BIN = kernel.bin
MBR_BIN = mbr.bin
OS_IMAGE = os_image.bin

CC = C:/bin/i686-elf-gcc.exe
LD = C:/i686-elf/bin/ld.exe
NASM = nasm
QEMU = "C:/Program Files/qemu/qemu-system-i386.exe"

CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector

all: $(OS_IMAGE)


# Link kernel
$(KERNEL_BIN): kernel_entry.o kernel.o idt.o idt_load.o isr.o isr_asm.o irq_asm.o io.o pic.o irq.o timer.o keyboard.o
	$(LD) -m elf_i386 -T linker.ld kernel_entry.o kernel.o idt.o idt_load.o isr.o isr_asm.o irq_asm.o io.o pic.o irq.o timer.o keyboard.o --oformat binary -o $(KERNEL_BIN)


# Assembly files

kernel_entry.o: kernel_entry.asm
	$(NASM) kernel_entry.asm -f elf -o kernel_entry.o

idt_load.o: idt_load.asm
	$(NASM) idt_load.asm -f elf -o idt_load.o

isr_asm.o: isr.asm
	$(NASM) isr.asm -f elf -o isr_asm.o

irq_asm.o: irq.asm
	$(NASM) irq.asm -f elf -o irq_asm.o


# C files

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

idt.o: idt.c
	$(CC) $(CFLAGS) -c idt.c -o idt.o

isr.o: isr.c
	$(CC) $(CFLAGS) -c isr.c -o isr.o

io.o: io.c
	$(CC) $(CFLAGS) -c io.c -o io.o

pic.o: pic.c
	$(CC) $(CFLAGS) -c pic.c -o pic.o

irq.o: irq.c
	$(CC) $(CFLAGS) -c irq.c -o irq.o

timer.o: timer.c
	$(CC) $(CFLAGS) -c timer.c -o timer.o

keyboard.o: keyboard.c
	$(CC) $(CFLAGS) -c keyboard.c -o keyboard.o


# Bootloader

$(MBR_BIN): MBR.asm
	$(NASM) MBR.asm -f bin -o $(MBR_BIN)


# Create OS image

$(OS_IMAGE): $(MBR_BIN) $(KERNEL_BIN)
	copy /b $(MBR_BIN)+$(KERNEL_BIN) $(OS_IMAGE)


# Run QEMU

run: $(OS_IMAGE)
	$(QEMU) -fda $(OS_IMAGE) -boot a


# Cleanup

clean:
	del *.o
	del *.bin