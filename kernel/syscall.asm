bits 32
global syscall_handler
extern syscall_dispatch

syscall_handler:
    pusha
    push esp
    call syscall_dispatch
    add esp, 4
    popa
    iretd
