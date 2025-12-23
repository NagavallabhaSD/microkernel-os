bits 32
global enter_user_mode
extern console_server
extern user_stack_top

enter_user_mode:
    cli

    ; Load user data segment
    mov ax, 0x23        ; user data selector (0x20 | 3)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push 0x23           ; SS
    push user_stack_top ; ESP (USER STACK ✅)
    pushf
    push 0x1B           ; CS (0x18 | 3)
    push console_server ; EIP
    iretd
