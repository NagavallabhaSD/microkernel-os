# Microkernel OS (x86, 32-bit)

This project is a **32-bit x86 microkernel-based operating system** developed from scratch for educational purposes.  
It demonstrates core OS concepts such as **paging, interrupts, IPC, and kernel services**, running in a VirtualBox virtual machine.

---

## Visualization on a Web page
- https://microkernel-visualiser.vercel.app/

---

## 🔧 Architecture Overview

- **CPU Mode:** x86 Protected Mode (32-bit)
- **Kernel Type:** Microkernel (minimal kernel, services separated)
- **Memory Management:** Paging with page-fault handling
- **Interrupt Handling:** IDT, PIC, hardware IRQs
- **Privilege Levels:** Ring 0 (kernel), Ring 3 (future user space)
- **Bootloader:** GRUB
- **Display:** VGA text mode

---

## ✨ Implemented Features

### Core Kernel
- Global Descriptor Table (GDT)
- Interrupt Descriptor Table (IDT)
- Task State Segment (TSS)
- Hardware interrupt handling (keyboard, timer-ready)
- Programmable Interrupt Controller (PIC) remapping

### Memory Management
- Paging enabled (CR0.PG)
- Identity-mapped page tables
- Page fault handler (INT 14)
- Safe kernel halt on invalid memory access

### Microkernel Components
- Inter-Process Communication (IPC) subsystem
- Kernel-mode console server (demo-safe)
- Modular service structure

### Demonstration Feature
- **Keyboard-triggered page fault**
  - Press `P` to deliberately access unmapped memory
  - Page-fault handler proves paging is active

---

## 🖥️ Demo Environment

- **Virtual Machine:** Oracle VirtualBox
- **RAM:** 512 MB
- **CPU:** 1 core
- **Architecture:** x86 (32-bit)
- **Host OS:** Windows 11 (via WSL)

---

## 🚀 How to Build & Run

### Prerequisites (Ubuntu / WSL)
```bash
sudo apt update
sudo apt install -y build-essential nasm grub-pc-bin xorriso qemu-system-x86
