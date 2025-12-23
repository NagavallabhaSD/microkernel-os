global page_fault_stub
extern page_fault_handler

page_fault_stub:
    cli
    pusha
    mov eax, cr2
    push eax
    push dword [esp + 36]
    call page_fault_handler
    add esp, 8
    popa
    hlt
