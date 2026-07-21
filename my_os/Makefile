KERNEL_BIN = kernel.bin
MBR_BIN = mbr.bin
OS_IMAGE = os_image.bin

CC = C:/bin/i686-elf-gcc.exe
LD = C:/i686-elf/bin/ld.exe
NASM = nasm
QEMU = "C:/Program Files/qemu/qemu-system-i386.exe"

CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector \
	-Ikernel \
	-Ikernel/cpu \
	-Ikernel/drivers \
	-Ikernel/memory


# ----------------------------------------
# Object Files
# ----------------------------------------

OBJECTS = \
	boot/kernel_entry.o \
	kernel/cpu/idt_load.o \
	kernel/cpu/isr_asm.o \
	kernel/cpu/irq_asm.o \
	kernel/kernel.o \
	kernel/cpu/idt.o \
	kernel/cpu/isr.o \
	kernel/cpu/irq.o \
	kernel/drivers/io.o \
	kernel/drivers/pic.o \
	kernel/drivers/timer.o \
	kernel/drivers/keyboard.o \
	kernel/drivers/vga.o \
	kernel/memory/pmm.o


# ----------------------------------------
# Build Everything
# ----------------------------------------

all: $(OS_IMAGE)


# ----------------------------------------
# Link Kernel
# ----------------------------------------

$(KERNEL_BIN): $(OBJECTS)
	$(LD) -m elf_i386 -T linker.ld $(OBJECTS) --oformat binary -o $(KERNEL_BIN)


# ----------------------------------------
# Assembly
# ----------------------------------------

boot/kernel_entry.o: boot/kernel_entry.asm
	$(NASM) boot/kernel_entry.asm -f elf -o boot/kernel_entry.o

kernel/cpu/idt_load.o: kernel/cpu/idt_load.asm
	$(NASM) kernel/cpu/idt_load.asm -f elf -o kernel/cpu/idt_load.o

kernel/cpu/isr_asm.o: kernel/cpu/isr.asm
	$(NASM) kernel/cpu/isr.asm -f elf -o kernel/cpu/isr_asm.o

kernel/cpu/irq_asm.o: kernel/cpu/irq.asm
	$(NASM) kernel/cpu/irq.asm -f elf -o kernel/cpu/irq_asm.o


# ----------------------------------------
# C Files
# ----------------------------------------

kernel/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel/kernel.o

kernel/cpu/idt.o: kernel/cpu/idt.c
	$(CC) $(CFLAGS) -c kernel/cpu/idt.c -o kernel/cpu/idt.o

kernel/cpu/isr.o: kernel/cpu/isr.c
	$(CC) $(CFLAGS) -c kernel/cpu/isr.c -o kernel/cpu/isr.o

kernel/cpu/irq.o: kernel/cpu/irq.c
	$(CC) $(CFLAGS) -c kernel/cpu/irq.c -o kernel/cpu/irq.o

kernel/drivers/io.o: kernel/drivers/io.c
	$(CC) $(CFLAGS) -c kernel/drivers/io.c -o kernel/drivers/io.o

kernel/drivers/pic.o: kernel/drivers/pic.c
	$(CC) $(CFLAGS) -c kernel/drivers/pic.c -o kernel/drivers/pic.o

kernel/drivers/timer.o: kernel/drivers/timer.c
	$(CC) $(CFLAGS) -c kernel/drivers/timer.c -o kernel/drivers/timer.o

kernel/drivers/keyboard.o: kernel/drivers/keyboard.c
	$(CC) $(CFLAGS) -c kernel/drivers/keyboard.c -o kernel/drivers/keyboard.o

kernel/memory/pmm.o: kernel/memory/pmm.c
	$(CC) $(CFLAGS) -c kernel/memory/pmm.c -o kernel/memory/pmm.o

kernel/drivers/vga.o: kernel/drivers/vga.c
	$(CC) $(CFLAGS) -c kernel/drivers/vga.c -o kernel/drivers/vga.o


# ----------------------------------------
# Bootloader
# ----------------------------------------

$(MBR_BIN): boot/MBR.asm
	$(NASM) -Iboot/ boot/MBR.asm -f bin -o $(MBR_BIN)


# ----------------------------------------
# OS Image
# ----------------------------------------

$(OS_IMAGE): $(MBR_BIN) $(KERNEL_BIN)
	copy /b $(MBR_BIN)+$(KERNEL_BIN) $(OS_IMAGE)


# ----------------------------------------
# Run
# ----------------------------------------

run: $(OS_IMAGE)
	$(QEMU) -fda $(OS_IMAGE) -boot a


# ----------------------------------------
# Clean
# ----------------------------------------

clean:
	del /Q *.bin 2>nul
	del /Q boot\*.o 2>nul
	del /Q kernel\*.o 2>nul
	del /Q kernel\cpu\*.o 2>nul
	del /Q kernel\drivers\*.o 2>nul
	del /Q kernel\memory\*.o 2>nul
