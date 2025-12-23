CC = gcc
AS = nasm

CFLAGS = -ffreestanding -m32 -nostdlib -fno-builtin -fno-stack-protector
LDFLAGS = -T boot/linker.ld -nostdlib -m32

all: iso

build:
	mkdir -p build

kernel.bin: build
	# Bootloader
	$(AS) -f elf32 boot/boot.asm -o build/boot.o

	# Core kernel
	$(CC) $(CFLAGS) -c kernel/kernel.c -o build/kernel.o
	$(CC) $(CFLAGS) -c kernel/gdt.c -o build/gdt.o
	$(CC) $(CFLAGS) -c kernel/idt.c -o build/idt.o
	$(CC) $(CFLAGS) -c kernel/tss.c -o build/tss.o
	$(CC) $(CFLAGS) -c kernel/paging.c -o build/paging.o

	# Kernel subsystems
	$(CC) $(CFLAGS) -c kernel/pic.c -o build/pic.o
	$(CC) $(CFLAGS) -c kernel/syscall.c -o build/syscall.o
	$(CC) $(CFLAGS) -c kernel/task.c -o build/task.o
	$(CC) $(CFLAGS) -c kernel/scheduler.c -o build/scheduler.o
	$(CC) $(CFLAGS) -c kernel/keyboard.c -o build/keyboard.o

	# IPC
	$(CC) $(CFLAGS) -c ipc/ipc.c -o build/ipc.o

	# Servers (kernel-mode for demo)
	$(CC) $(CFLAGS) -c servers/console.c -o build/console.o

	# Assembly helpers
	$(AS) -f elf32 kernel/gdt_flush.asm -o build/gdt_flush.o
	$(AS) -f elf32 kernel/tss_flush.asm -o build/tss_flush.o
	$(AS) -f elf32 kernel/kernel_stack.asm -o build/kernel_stack.o
	$(AS) -f elf32 kernel/syscall.asm -o build/syscall_asm.o
	$(AS) -f elf32 kernel/context_switch.asm -o build/context_switch.o
	$(AS) -f elf32 kernel/irq0.asm -o build/irq0.o
	$(AS) -f elf32 kernel/irq.asm -o build/irq.o
	$(AS) -f elf32 kernel/page_fault.asm -o build/page_fault.o

	# Link everything
	$(CC) $(LDFLAGS) \
		build/boot.o \
		build/kernel.o \
		build/gdt.o build/gdt_flush.o \
		build/idt.o \
		build/tss.o build/tss_flush.o \
		build/paging.o \
		build/kernel_stack.o \
		build/syscall.o build/syscall_asm.o \
		build/pic.o \
		build/irq0.o build/irq.o \
		build/page_fault.o \
		build/task.o \
		build/scheduler.o build/context_switch.o \
		build/keyboard.o \
		build/ipc.o \
		build/console.o \
		-o build/kernel.bin

iso: kernel.bin
	mkdir -p iso/boot/grub
	cp build/kernel.bin iso/boot/kernel.bin
	cp boot/grub.cfg iso/boot/grub/
	grub-mkrescue -o build/microkernel.iso iso

clean:
	rm -rf build iso
